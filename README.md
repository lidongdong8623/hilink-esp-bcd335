# hilink-esp-bcd335
hilink and  esp8266  for bcd335.

ssh-keygen -t rsa -b 4096 -C xxxxxxx@xxx.com
cd /home/esp8266/.ssh/
cat id_rsa.pub
copy to github sshkey。


git clone git@github.com:lidongdong8623/hilink-esp-bcd335.git
git add .
git commit -a
git push


cp -rf Device_Project /home/esp8266
cd /home/esp8266/Device_Project/application

./gen_misc.sh

ls /home/esp8266/Device_Project/bin

ESP-WROOM-02D:
bin\eagle.irom0text.bin	                                0x10000
bin\eagle.flash.bin	                                0x00000
ESP8266_RTOS_SDK-2.0.0\bin\blank.bin	                0x1fb000
ESP8266_RTOS_SDK-2.0.0\bin\blank.bin	                0x1fe000
ESP8266_RTOS_SDK-2.0.0\bin\esp_init_data_default.bin	0x1fc000



26M
40MHz
QIO
16Mbit-C1

./gen_misc.sh
Y
0
2
0
5

-rwxrwxrwx 1 root root 3.8M  1月 26 12:14 eagle.dump
-rwxrwxrwx 1 root root 9.4M  1月 26 12:14 eagle.S
-rwxrwxrwx 1 root root 560K  1月 26 12:14 eagle.irom0text.bin
-rwxrwxrwx 1 root root  38K  1月 26 12:14 eagle.flash.bin

