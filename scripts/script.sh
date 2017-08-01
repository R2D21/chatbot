rec -c 2 -r 16000 -c 1 data/record.flac trim 0 5;
wget -q --post-file data/record.flac --header="Content-Type: audio/x-flac; rate=16000" -O - "https://www.google.com/speech-api/v2/recognize?client=chromium&lang=fr_fr&key=AIzaSyAcalCzUvPmmJ7CZBFOEWx2Z1ZSn4Vs1gg" > data/test.json
