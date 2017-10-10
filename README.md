# Device_Driver
This is a character device driver where a device takes input string and reflects back reverse of the taken string as output.
Only one process can write to the device at a time.
when there is no data to read the process will be in sleep state and this process will be awake only after some other process writes data to the device.
