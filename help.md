Welcome to Helpdesk...
This is the help section.
Commands for file manipulation-

 c [file_name]                                                      This command is used to create a file with default permission 0777 (eg.:  c f1.txt)
 r [file_name] [*bytes_to_seek] [*no_of_bytes]                      This command to read a file. (eg.:  r f1.txt  ||  r f1.txt 100  ||  r f1.txt 100 10)
 w [file_name] [*bytes_to_seek]                                     This command is used to write text in file. It take input from console.
                                                                    (eg.:  w f1.txt  ||  w f1.txt 100)
 wt [file_name] [*bytes_to_seek]                                    This command is used to truncate the file. (eg.:  wt f1.txt  ||  wt f1.txt 100)
 a [file_name] [*bytes_to_seek]                                     This command is used to append text in file. It take input from console. 
                                                                    (eg.:  a f1.txt  ||  a f1.txt 100)
 cp [source_file] [target_file] [*bytes_to_seek] [*no_of_bytes]     This command is used to copy a file into another file. 
                                                                    (eg.:  cp f1.txt f2.txt ||  cp f1.txt f2.txt 100  ||  -p f1.txt f2.txt 100 10)
 d [file_name]                                                      This command is used to get statical information of a file. (eg.:  d input.txt)
 help                                                               This command is used access help regarding commands. (eg.:  help)

[file_name]         - name of file which you want to perform operation.
[no_of_bytes]       - how many bytes you want to read (integer).
[bytes_to_seek]     - no of bytes want to skip (integer).
[source_file]       - name of file from which you want to copy.
[target_file]       - name of file in which you want to copy.

* - not required
Note:   File will be created with default permission 0777 if not exist while opening. 
        ./a is mandatory before command