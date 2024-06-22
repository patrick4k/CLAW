CLAW (Command Line Audio Workstation)

Its like a DAW (Digital Audio Workstation), but from the command line!

This is primarily a place for me to experiement with audio processing and so I can play my bass without an amp.

Example execution:
```
[LOG] [class claw::apps::CommandLineApp] Enter command:
[INPUT] start
[LOG] [class claw::io::AudioProcessor] Audio device started: Sample Rate = 44100.000000, Buffer Size = 441
[LOG] [class claw::io::AnalogAudioDevice] Input Device: Microphone (Scarlett Solo USB)
[LOG] [class claw::io::AnalogAudioDevice] Output Device: Speakers (Scarlett Solo USB)
[LOG] [class claw::apps::CommandLineApp] Enter command: 
[INPUT] stop
[LOG] [class claw::io::AudioProcessor] Audio device stopped
[LOG] [class claw::apps::CommandLineApp] Enter command: 
[INPUT] exit
[LOG] Exiting application...
[LOG] Exiting Program...

Process finished with exit code 0.
```

