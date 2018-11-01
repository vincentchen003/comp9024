max = find /users/apple/documents/comp9041/test1|ls -l|sort -k4r|cut -c 29-32|head -1
echo "max is $max"