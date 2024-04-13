Switchless JiffyDOS for Arduino

This is an implementation for Arduino of a Switchless JiffyDOS. What the hell is this?

Well, usually when using JiffyDOS one will use a switch on line A12 of a 27C512. This acts
like a bank switch that will choose between stock Commodore KERNAL, or JiffyDOS.

Since we don't want to drill holes on our C64s, the option is instead to exploit the fact
that the RESTORE key in the C64 is wired directly and it's not part of the keyboard matrix.

So this controller uses 3 pins:

D0 goes to the C64's RESET bus.
D1 goes to the RESTORE key
D2 goes to 27C512's A12 line.

How it works

At boot, it'll set D2 high.

Then it will listen for the RESET line and wait for it to go down. When the RESET line is low,
it will sample the RESTORE line. If RESTORE is high, it'll keep the A12 line latched HIGH.
If restore is low, it'll keep A12 line latched LOW.

It keeps the latch for as long as RESET is HIGH (normal operation).

So, when you turn on your C64 it'll default to JiffyDOS. If you want Stock KERNAL, you can hold RESTORE
and power cycle the machine, or use any reset switch you have (cartridges etc).

I've tried this with an ATtiny412 with megaTinyCore, but this works with ANY Arduino that works with 5V.
