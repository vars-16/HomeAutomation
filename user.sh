echo "Enter your name: " > /dev/pts/1
read name < /dev/pts/1

if [ "$name" = "wireless" ]
then
	echo "Authentication successful !!!" > /dev/pts/1
else
	echo "Unauthorized access in your home." | ssmtp mohitvars.zhcet@gmail.com
fi