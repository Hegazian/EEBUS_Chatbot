#! /bin/bash

# Todo: find out how this can be done automatically
/etc/init.d/dbus start

# Todo: --no-chroot required, otherwise avahi-daemon only starts
# in the first docker container instance
# Find a cleaner solution!
avahi-daemon --no-chroot &

timeout 120 \
  keo_framework_example_simple_client \
  -c /tmp/example-client.json \
  --log-config=/tmp/example-client.log.config \
  --log-level=2

