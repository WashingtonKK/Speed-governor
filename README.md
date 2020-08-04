I am making a speed governor firmware.

Using NEO 6M GPS module, SIM800L and STM32 bluepill.

The velocity of the vehicle is read from the vehicle tachometer  whose signal pin is connected to pin A10

This velocity is also compared to the velocity read from the GPS module to determine whether the vehicle is in true motion.

At a peak velocity of 80km/h, the fuel supply is regulated to ensure the vehicle does not exceed the speed limit.

All data is sent to our server and accessible via sms, web or mobile application.