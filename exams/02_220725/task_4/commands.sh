find /home -maxdepth 1 -name '*.c' | wc --lines                         # 1
cat ~/*.c | grep -E " main ?(\w*)" | wc --lines                         # 2
cat phones.info | grep -E "(0|+359)8[789]\d{7}"                         # 3.1
cat phones.info | grep -E "[^((0|+359)8[789]\d{7})]" | wc --lines       # 3.2
cat phones.info | grep -E "(0|+359)87\d{7}" > phones.vivacom.data       # 3.3
