bin/bash
echo "___Package Manager___"
echo "This script will check if wanted repo is installed and install it"
echo "made be Mark Gordienko 737-1"
loop="y"
while [ "$loop" == "y" ]
do
        echo "___Installed repos___"
        cat /etc/apk/repositories
        echo "Enter wanted repo"
        read repo
        echo "$repo"
        result=$(grep "$repo" /etc/apk/repositories)
        if [[ "$result" != "" ]];
                then
                echo "Wanted repo is already installed:"
                echo "$result"
        else
                echo "Wanted repo is not installed! Enter repo url:"
                read spec
                echo "@$repo $spec" | tee -a /etc/apk/repositories
                echo "New repo added!"
                cat /etc/apk/repositories
        fi
echo "Do you want to continue? y/n"
read loop
done