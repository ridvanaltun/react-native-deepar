# Interfaces

TypeScript interfaces

## IStartRecording

| Key                         | Default Value                  | Required     | Description                                                                                | Android                     | iOS                         |
| --------------------------- | ------------------------------ | ------------ | ------------------------------------------------------------------------------------------ | --------------------------- | --------------------------- |
| width                       | <div align="center">-</div>    | <b>false</b> | Video width                                                                                | <div align="center">+</div> | <div align="center">+</div> |
| height                      | <div align="center">-</div>    | <b>false</b> | Video height                                                                               | <div align="center">+</div> | <div align="center">+</div> |
| recordAudio                 | <div align="center">true</div> | <b>false</b> | Record audio during video recording.                                                       | <div align="center">+</div> | <div align="center">+</div> |
| quality                     | <div align="center">-</div>    | <b>false</b> | A key to set the JPEG compression quality of the video. The corresponding value is 0.0-1.0 | <div align="center">-</div> | <div align="center">+</div> |
| bitrate                     | <div align="center">-</div>    | <b>false</b> | A key to access the average bit rate—as bits per second—used in compressing video.         | <div align="center">+</div> | <div align="center">+</div> |
| maxKeyFrameInterval         | <div align="center">-</div>    | <b>false</b> | A key to access the maximum interval between keyframes.                                    | <div align="center">+</div> | <div align="center">+</div> |
| maxKeyFrameIntervalDuration | <div align="center">-</div>    | <b>false</b> | A key to access the maximum interval duration between keyframes.                           | <div align="center">-</div> | <div align="center">+</div> |
