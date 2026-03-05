kill -l is the man page

You cna produce a core intentionally by SIGQUIT
SIGKILL kills the terminal
SIGCHILD is ignored and sends a signal to the parent once the child exits.

SIGWIN sends a signal when the Window gets resized

SIGKILL and SIGSTOP cannot be changed

Split into 2 terminals

run loop.cpp in one, in the other try ps -fu to get the process id, kill process ID to mimmick ctrl z, kill -STOP process id
kill -CONT pid to continue to mimmick ctrl Q

we can also do pkill -STOP a.out to kill all our instances of a specific process

remove signal sigwinch to child

if [ "$#" -ne 1 ] ; then
    echo "Usage: ./backup.sh dirName"
    exit 1
fi  # Check if the user has provided exactly one command line argument

# The directory name provided by the user
dirName=$1

# Check if the directory already exists
if [ -d "$dirName" ] ; then
    echo "Directory $dirName already exists...Please use a different name"
    exit 1
fi

# Create the directory
mkdir "$dirName"

# Copy all .c and .h files into the new directory
cp *.c *.h "$dirName" $dirName>/dev/null

# Check if any .c or .h files were copied, otherwise print an error
if [ $? -eq 0 ] ; then
    echo "Files copied successfully to $dirName"
else
    echo "cp: cannot stat '*.c': No such file or directory"
    echo "cp: cannot stat '*.h': No such file or directory"
fi