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


