#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
from random import choice, randint, seed
import subprocess
import threading
from time import sleep

""" This script starts N SPINE example clients. Place it in the keo_spine bin directory"""

###################### CONFIGURE HERE ##################################

# Maximum number of clients
NUM_CLIENTS = 20

# Start all clients at the beginning
START_INITIAL = False

# Randomly start/stop clients
TOGGLE_CLIENTS = True

# Min/max time in milliseconds between next 'toggle'
TOGGLE_TIME = (500, 3000)

# Port number of the first client (nth client gets port number PORT_BASE+n)
PORT_BASE = 4700

# Where to put config files, log files, etc.
OUTPUT_DIR = '/tmp/connect-spine/'

# Make sure this path is correct
GENERATE_KEYS_SCRIPT = "../../../../../src/keo_spine_0.0.0/keo_spine/scripts/generateKeys.sh"

########################################################################

CFG_TEMPLATE = """{{
   "DeviceConfiguration" : {{
      "CertificateFullFilename" : "{cert_path}",
      "ConnectionHost" : "0.0.0.0",
      "ConnectionPort" : {port},
      "DeviceBrand" : "connect",
      "DeviceModel" : "connect",
      "DeviceType" : "connect",
      "EEBusDevice" : "{spine_id}",
      "InstanceName" : "connect",
      "PrivateKeyFullFilename" : "{key_path}",
      "ShipId" : "{ship_id}",
      "TruststoreFullFilename" : "/tmp/{ship_id}.truststore.json"
   }}
}}"""


class TestNode():
    def __init__(self, cid, certFile, keyFile, trustFile):
        self.cid = cid
        self.cfgFile = OUTPUT_DIR + str(cid) + '_spine.config'
        self.certFile = certFile
        self.keyFile = keyFile
        self.logFile = OUTPUT_DIR + str(cid) + '_log.txt'
        self.trustFile = trustFile


class SubprocessThread(threading.Thread):
    def __init__(self, client):
        threading.Thread.__init__(self)
        self.client = client

    def run(self):
        print('START client ' + str(self.client.cid))
        with open(self.client.logFile, 'w') as logFile:
            self.proc = subprocess.Popen(['./keo_framework_example_simple_client', '--config',
                OUTPUT_DIR + str(self.client.cid) + '_spine.config'], stdout=logFile, stderr=logFile)
        self.proc.wait()

    def stop(self):
        if self.isAlive():
            print('STOP client ' + str(self.client.cid))
            self.proc.kill()


def main():
    try:
        os.mkdir(OUTPUT_DIR)
    except FileExistsError:
            pass
    
    # Fixed seed for reproducability, change if you want
    seed(4000)

    clients = []

    for cid in range(1, NUM_CLIENTS + 1):
        os.system(GENERATE_KEYS_SCRIPT + ' ' + OUTPUT_DIR + str(cid) + ' --batch')
        client = TestNode(cid, OUTPUT_DIR + str(cid) + '_prime256v1CertDER.bin', OUTPUT_DIR + str(cid) +
                '_prime256v1KeyDER.bin', OUTPUT_DIR + str(cid) + '_truststore.json')
        clients.append(client)

        with open(client.cfgFile, 'w') as f:
            cfg = CFG_TEMPLATE.format(ship_id='ship' + str(client.cid),
                    spine_id='d:_i:1_connect' + str(client.cid), cert_path=client.certFile,
                    key_path=client.keyFile, port=PORT_BASE + client.cid)
            f.write(cfg)

    processThreads = {}

    for client in clients:
        t = SubprocessThread(client)
        processThreads[client.cid] = t
        if START_INITIAL:
            t.start()

    if TOGGLE_CLIENTS:
        try:
            while True:
                randomThread = choice(list(processThreads.values()))
                if randomThread.is_alive():
                    randomThread.stop()
                else:
                    newThread = SubprocessThread(randomThread.client)
                    processThreads[randomThread.client.cid] = newThread
                    newThread.start()

                print('Currently running: {}'.format(len([t for t in processThreads.values() if
                                                     t.is_alive()])))
                sleep(randint(TOGGLE_TIME[0], TOGGLE_TIME[1]) / 1000.0)
        except KeyboardInterrupt:
            for t in processThreads.values():
                t.stop()

    # wait for processes to finish
    for p in processThreads.values():
        if p.is_alive():
            p.join()


if __name__ == '__main__':
    main()
