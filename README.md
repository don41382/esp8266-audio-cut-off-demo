
# convert songs to safe space
```for f in *.aif; do ffmpeg -i $f -ac 1 -ab 32k -ar 22050 -map 0:a:0 "${f%.aif}.mp3" ; done```