This file maintains a chronological list of quick notes.
==========================================================
maintained by, Anshuman Dhuliya (anshumandhuliya@gmail.com)

------------------------------------------------
Getting the basic information about a linux system. <a name="20150617-130212"></a>
================================================
* Keywords: management
* Timestamp: 20150617-130212

------------------------------------------------
------------------------------------------------

1. `uname -a`, `uname -snrvmo` gives the kernel name, node name, kernel-release, kernel-version, machine arch, operating system

2. For more information also use

        /proc/version
        lsb_release -a      # lsb = Linux Standard Base, provides
        # distribution specific information.
        /etc/os-release and /etc/lsb-release

3. View the command line used to invoke the running kernel:

        cat /proc/cmdline
        

    # view the environment desktop applications receive
    # on gnome press Alt-F2 and enter the following,
    xterm -e bash --noprofile --norc

------------------------------------------------





------------------------------------------------
Himani Shivpuri <a name="20150618-101614"></a>
================================================
* Keywords: himani shivpuri, mummy, random
* Timestamp: 20150618-101614

------------------------------------------------
------------------------------------------------

Himani Shivpuri -- Mummy's Childhood Friend a Movie Actor

------------------------------------------------





------------------------------------------------
python subprocess module <a name="20150618-105614"></a>
================================================
* Keywords: himani shivpuri, mummy
* Timestamp: 20150618-105614

------------------------------------------------
------------------------------------------------

Revise the subprocess module of python3, from docs.python.org. See also shutil and os module for more help.

shlex.split() - for splitting a string that is like shell arguments [GOOD]
Python
1. Execute the command using the shell and wait - output goes to sys.stdout

        subprocess.call('ls -l', shell=True) -- wait for the command to complete.
        os.system('ls -l') # returns the process return/exit/status code

2. Execute the command and receive the output as a string/list of strings.

        output = subprocess.getoutput('ls -l') # stdout and stderr both joined
        output = subprocess.getstatusoutput('ls -l') # same as getoutput, but with return code
        output = subprocess.check_output('ls -l', shell=True, stderr=subprocess.DEVNULL, universal_newlines=True) # throws exception when the command returns a non-zero exit code. The exception has the 'returncode' and the 'output' in it. Use this when stderr is not required by directing it to DEVNULL.

3. Execute the command and setup a pipe to its stdin and stdout

        p = subprocess.Popen('wc', shell=True, stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                universal_newlines=True)
            Now interact with the program via p.stdin and p.stdout
        # Same as above but get the output line by line instead of waiting for all
        # of it.
        p = subprocess.Popen('wc', shell=True, stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                universal_newlines=True, bufsize=1)

References
---------------
<https://pymotw.com/2/subprocess/> (good)

------------------------------------------------


------------------------------------------------
Package management in ubuntu <a name="20150624-164621"></a>
================================================
* Keywords: ubuntu package management, program management
* Timestamp: 20150624-164621

------------------------------------------------
------------------------------------------------

Some programs useful for package management
----------------------------------------------
1. `dpkg` - managing local packages
1. `apt-get` - installs from repositories
1. `apt-cache` - search packages, get information about packages
1. `apt` - a new utility to replace apt-get, apt-cache etc.
1. `apt-file` - file related info -- needs install
1. `dlocate` - locates file in packages -- needs install
1. `auto-apt` - installs pkgs hinted in ./configure scripts -- needs install
1. `apt-rdepends` - lists recursive dependencies of given package -- needs install

Some frequent jobs
-------------------------
1. Which packages are installed on the system?

        dpkg --list  # or dpkg -l
        dpkg --list *<search_term>* # filters by package name

2. What files were in/installed-by package XYZ?

        apt-file list PACKAGE
        dpkg --listfiles INSTALLED-PACKAGE  # or dpkg -L PACKAGE
        dpkg --contents foo.deb # or dpkg -c foo.deb

3. What package provides the file '/usr/include/curses.h' ?

        dpkg --search /usr/include/curses.h

        # general search -- `apt-file` needs install.
        # run : `apt-file update` before any usage
        # It searches ALL packages in the repositories.
        apt-file search curses.h
        apt-file search /usr/include/curses.h # exact search

        dlocate curses.h # fastest way to search -- install dlocate first

4. How to get the information about a package?

        apt-cache show PACKAGE # gives information about the package
        apt-cache policy PACKAGE # is the package installed?
        dpkg --listfiles INSTALLED-PACKAGE # gives the files of the PACKAGE
        dpkg --status INSTALLED-PACKAGE # gives status/details about the PACKAGE

        dpkg --contents PACKAGE.deb # shows the files in the deb file
        dpkg --info PACKAGE.deb     # info on the deb file

        apt-cache depends PACKAGE # only shows depedencies
        apt-cache rdepends [--recurse] PACKAGE # shows reverse dependencies
        apt-rdepends PACKAGE    # (recursive) dependecies of PACKAGE

        apt-file show PACKAGE       # (show/list) files in a package

5. How to install and remove packages in ubuntu?

        sudo dpkg --install PACKAGE.deb

        # Fix dependency problems caused by raw usage of,
        # `dpkg --install ...` command.
        # or in any other case in general.
        sudo apt-get install --fix-broken   # or use `-f` option

        # use option `--ignore-depends=PACKAGE` to
        # ignore dependency problems.
        # Use `--dry-run` to foresee whats going to happen.
        sudo dpkg --remove INSTALLED-PACKAGE  # Remove. dependent packages will fail
        sudo dpkg --purge INSTALLED-PACKAGE  # Purge. deletes associated config files too

        sudo apt-get install PACKAGE # fresh installation
        sudo apt-get install --reinstall INSTALLED-PACKAGE

        # use option `--dry-run` to foresee what will happen
        # on removing/purging/reinstalling a package to prevent pain
        sudo apt-get remove INSTALLED-PACKAGE  # del package
        sudo apt-get purge INSTALLED-PACKAGE  # del config files too 

5. How to update/ upgrade system and its packages?

        sudo apt-get update  # updates package list from set repositories
        apt list --upgradable  # list of upgradable packages (run `apt update` before this)
        sudo apt-get upgrade  # install newest version of all packages currently installed
        sudo apt-get upgrade INSTALLED-PACKAGE  # upgrade a package
        sudo apt-get dist-upgrade  # upgrade distribution


6. What are some other convenience utilities available for package management?

        # automatically installs missing packages
        # whose officially known files are accessed by configure.
        auto-apt run ./configure

7. What are the important files/directories for package management?

        /var/cache/apt/archives/    #cached downloaded .deb files 
        /var/log/apt/history.log    #history of commands and more info
        /etc/apt/apt.conf           # create one if not exists
        /etc/apt/apt.conf.d/
        /etc/apt/sources.list
        /etc/apt/sources.list.d/

8. Some operations on packages.

        dpkg --extract package.deb <directory> # extracts from the archive
        dpkg --vextract package.deb <directory> # as above with verbosity

9. Download packages

        apt-get download PACKAGE

        # download package and all its dependecies
        # some rare packages may not download,
        # their name given by apt-rdepends might be different
        # apt-rdepends : rcursive dependencies (not reverse)
        # Downloading a package and all its dependencies in the current directory:

        apt-get download $(apt-rdepends PACKAGE | grep -v "^ ")

------------------------------------------------





------------------------------------------------
Effect of music on plants <a name="20150909-164620"></a>
================================================
* Keywords: effect of music on plants
* Timestamp: 20150909-164620

------------------------------------------------
------------------------------------------------

Resource: <http://www.dovesong.com/positive_music/plant_experiments.asp>

In 1973, a woman named Dorothy Retallack published a small book called **The Sound of Music and Plants**. Her book detailed experiments that she had been conducting at the Colorado Woman’s College in Denver using the school’s three Biotronic Control Chambers. Mrs. Retallack placed plants in each chamber and speakers through which she played sounds and particular styles of music. She watched the plants and recorded their progress daily. She was astounded at what she discovered.

Next Mrs. Retallack tried another experiment again using the three chambers. In one chamber she played North Indian classical music performed by sitar and tabla, in another she played Bach organ music, and in the third, no music was played. THE PLANTS "LIKED" THE NORTH INDIAN CLASSICAL MUSIC THE BEST. In both the Bach and sitar chambers, the plants leaned toward the speakers, but the plants in the Indian music chamber leaned toward the speakers the most.

------------------------------------------------





------------------------------------------------
concurrency and parallelism <a name="20150627-164620"></a>
================================================
* Keywords: concurrency, parallelism
* Timestamp: 20150627-164620

------------------------------------------------
------------------------------------------------

* discover kotlin and its concurrency model (TODO)

* Erlang and Concurrency

OTP = general set of servers and supervisor implementations (golang needs a manual workout for this feature -- look how?)

Erlang uses Actor Model of Concurrency and Golang uses CSP(Communicating Sequential Processes) model.

* Concurrency and Parallelism need different tools. <http://yosefk.com/blog/parallelism-and-concurrency-need-different-tools.html>
* One more thing to look at is how Haskell models concurrency. Haskell it seems is a pretty smart functional language.
* Concurrency vs Parallelism
* Linearizability vs Serializability and Strict Serializability


------------------------------------------------





------------------------------------------------
RIMINET <a name="20150627-164620"></a>
================================================
* Keywords: research for riminet
* Timestamp: 20150627-164620

------------------------------------------------
------------------------------------------------

Tue Jun 30 12:21:13 IST 2015

* Hylozoism - universe is in some sense alive

* prosthetic (prosthetic limb...), comeuppance

* Philosophical topic: At the tip of the blind man's stick.

* Good Quote from Malafouris' book: 'How things shape the mind'

" Mind, as the philosopher Andy Clark notes in his book Being There, 'is a leaky organ, forever escaping its `natural` confines and mingling shamelessly with body and with world' (1997, 53)."


### Wed Jul  1 09:37:10 IST 2015

*Philosophy -- Wikipedia

Philosophy is the study of general and fundamental problems, such as those connected with reality, existence, knowledge, values, reason, mind and language.

Etymology: 'philosophia' greek, probably from Pythagoras, meaning 'love for wisdom' or 'friend of wisdom'.

Terms: analytic philosophy(based on reasoning), epistemology -- relationship b/w truth, belief, perception and theories of justification; skepticism, regress argument -- infinitism, foundationalism, coherentism; Munchhausen trilemma, Rationalism vs Empiricism, mental content

*A Cognitive Leakage into the world -- Malafouris


### Sat Jul 25 14:33:14 IST 2015

Can 'language' express our intelligence explicitly ? If yes, then how? If no, then what is needed more? -- intuitively language is only the tip of the iceberg. It can express a small set of our emotions/intent. Other factors like facial expression, body language carry much information. However, language is known to affect the growth and shape our intellect.

------------------------------------------------





------------------------------------------------
web development <a name="20151015-160647"></a>
================================================
* Keywords: webdev, website, application, web development
* Timestamp: 20151015-160647

------------------------------------------------
------------------------------------------------

Good resource for a web application development model.

<http://www.codeproject.com/Articles/10746/Dude-where-s-my-business-logic#Introduction>

some web dev components
--------------------
* word/phrase auto-completions
* search functionality
* automated email
* automated sms
* sms OTP facility
* image optimization
* interactive image cropping
* QR code scanner
* bar code code scanner
* video optimization

------------------------------------------------





------------------------------------------------
Computer Languages <a name="20151117-204744"></a>
================================================
* Keywords: computer languages, language properties
* Timestamp: 20151117-204744

------------------------------------------------
------------------------------------------------

Overview of computer languages:
* Compiled, interpreted, or JIT-compiled
* High or low level
* Type System
  1. Type Strength: Strong or Weak
  1. Type Checking: Static or Dynamic
  1. Type Safety: Safe or Unsafe
  1. Type Expression: Manifest or Inferred
* Supported Paradigms
  1. Declarative (what-to-do)
     a. Functional (avoids states and mutable variables)
  2. Imperative (instructions exactly how-to-do)
     a. Structured
     a. Procedural
     a. Object-Oriented
* Generic (e.g. templates in C++)
* Self-hosting Compiler

Resource:
----------

<http://www.cplusplus.com/info/description/>

------------------------------------------------





------------------------------------------------
Image Commands <a name="20170519-092125"></a>
================================================
* Keywords: file management, jpeg, picture, pics, photos 
* Timestamp: 20151117-204744

------------------------------------------------
------------------------------------------------

Managing images

Resize/Rotate Images:

    sudo apt-get install nautilus-image-converter

Now restart nautilus `nautilus -q` and two items in *context* menu will be added,
Resize and Rotate. AND/OR

    convert  -resize 1024X768  source.png dest.jpg

Create a thumbnail of a picture with width 300:

    convert -thumbnail 300 pic1.jpg thumb.pic1.jpg

Create a thumbnail of a picture with height 300:

    convert -thumbnail x300 pic1.jpg thumb.pic1.jpg

Reduce a jpeg image to 50% quality and store in folder 'compressed'

    jpegoptim -m50 -d compressed/ pic1.jpg pic2.jpg pic3.jpg

Identify dimensions of an image:

    idenfity -format "%w" image.jpg; #getwidht

    idenfity -format "%h" image.jpg; #getheight

Image information:
* exif (Exchangeable Image Format),
* iptc (International Press Telecommunications Council),
* xmp (Extensible Metadata Platform)

------------------------------------------------





------------------------------------------------
MySql Database Notes <a name="20160313-014443"></a>
================================================
* Keywords:  mysql database usage, mysql commands, mysql management
* Timestamp: 20160313-014443

------------------------------------------------
------------------------------------------------

Creating a new user in mysql and granting privileges:
----------------------------------------------

1. Login to the `mysql` shell (note that root password is set when installing MySql).

        $ mysql -u root -p
        Enter password:
        Welcome to the MySQL monitor. Commands end with ; or \g.
        ...
        mysql>


2. Create a user `codeman`:

        mysql> create user 'codeman'@'%' identified by 'anshuisneo';
        Query OK, 0 rows affected (0.00 sec)

   Creates a user `codeman` that can login from any domain. `%` can be replaced with `localhost` or some complete (e.g. `mail.google.com`) or partial domain (e.g. `%.google.com`).

3. Grant priviledges to the user,

        mysql> GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP ON testdb.* TO 'codeman'@'%' IDENTIFIED BY 'anshuisneo';
        Query OK, 0 rows affected (0.00 sec)
        mysql> FLUSH PRIVILEGES;

   now you can login as 'codeman' (password: anshuisneo)  and use 'testdb' database as required from any system.


Creating a user with only backup privileges
-------------------------------------------

1. Create the user,

        mysql> CREATE USER 'backup'@'localhost' IDENTIFIED BY 'password';

2. Grant backup permissions,

        mysql> GRANT LOCK TABLES, SELECT ON <dbname>.* TO 'backup'@'localhost';
        mysql> FLUSH PRIVILEGES;

Removing a User
-------------------

    DROP USER [IF EXISTS] 'codeman'@'localhost';

Note that, `DROP USER` doesn't affect current live sessions of the the dropped user. However, user's next login attempt will not be allowed. This is by design.


Backup Database
-------------------------
keywords: backup database, backup mysql database

1. backup database (Uncompressed)

        mysqldump -u <user> -p <db_name> > <file_name>.sql


2. backup database (Compressed)

        mysqldump -u <user> -p <database_name> | gzip > <file_name>.sql.gz
 
   `gzip` can be replaced with `bzip2` too (then the appended extension will become `.bz2`). PHPMyAdmin accepts `.gz` and `.bz2` files for upload, so its recommended to compress the databases.

`user` should have backup priviledges i.e. `LOCK TABLES` and `SELECT` permissions.


Restore Database
---------------------
keywords: restore database, restore mysql database

1. Create the database first

        $ mysql -u <user> -p
        mysql> CREATE DATABASE <db_name>;

2. Create a user specifically for the database (good security measure)

        mysql> GRANT ALL PRIVILEGES ON <db_name>.* TO <new_user>@<hostname> IDENTIFIED BY <new_user_password>;
        mysql> exit;

3. Finally run the following command and you are done.

        mysql -u <new_user> -p <db_name> < <file_name>.sql


Running an SQL script file in mysql
---------------------------------

    mysql -u <user> -p -t < employees.sql


Some useful commands
----------------------

    show databases;
    use <databasename>;

    show tables;
    describe <tablename>;
    select columns from <tablename>; # shows information on columns of table 'tablename'
    show index from <tablename>;
    show table status like 'tablename'; # show MySql RDBMS performance stats

Creating a table in Mysql:
--------------------------

    mysql> CREATE TABLE tutorials_tbl(
       -> tutorial_id INT NOT NULL AUTO_INCREMENT,
       -> tutorial_title VARCHAR(100) NOT NULL,
       -> tutorial_author VARCHAR(40) NOT NULL,
       -> submission_date DATE,
       -> PRIMARY KEY ( tutorial_id )
       -> );


MySql Tools
------------------

1. DbVisualiser : a database visualization tool as sql client (download [here](https://www.dbvis.com/download/))

------------------------------------------------





------------------------------------------------
leave and licence agreement rent agreement information <a name="20160313-014443"></a>
================================================
* Keywords:  licence agreement
* Timestamp: 20160316-124222

------------------------------------------------
------------------------------------------------

rental information(good): (leave and licence agreement)
https://arathimy.wordpress.com/2015/03/18/getting-your-leave-and-license-agreement-registered-in-mumbai/

Data Entry Number (https://pdeigr.maharashtra.gov.in/PDE-REGISTRATION-USER/Helpfile.aspx):
87418160316

EChallan (GRAS GRN number from https://gras.mahakosh.gov.in/echallan/):
PDF reciept at my google drive folder 'rent-agreement'
Stamp duty(amount 500): MH008105530201516P
Registration(amount 1000): MH008107096201516E

Shree Vijay Vihar:
  Society Info:
  IIT (Mumbai) Employees Co-Operative Housing Society Limited
  Registration No. BOM/WS/HSG/(TO)8592/99-200 
  Plot N. V
  CST No. 1/17 (PT) & 6
  dated 24.06.1999

  Address:
  Shree Vijay Vihar
  Near Powai Vihar Hsg. Complex
  Village - Kopari
  S-ward, Zone 118, Sub zone 545,
  Off Adi Shankaracharya Marg,
  Powai, Mumbai - 400076


Office address and timings:
<http://igrmaharashtra.gov.in/SB_ORGANISATION/ORGANISATION_Offices.aspx>

Office that we will go to:
Jt. Sub Registrar Kurla 4 
Exzim Link Complex,Opp. Indira
Container yard Nahur (W)
Mumbai 80, 2 Pm to 9 pm (Every
Sunday, Second and
Fourth Saturday)

Villages in Mumbai Sub-urban district:
<http://e-stampdutyreadyreckoner.com/Villages_In_Mumbai_Suburban_District.html>

### Comment on arathimy.wordpress.com/...

Thanks a LOT!!! This was very very useful. I renewed my LandL agreement without any agent by following your given guidelines.

Also, the SARATHI helpline no. 8888007777 was really helpful while filling the Public Data Entry form. It is amazing how a government helpline could be so helpful, they were patient, they clearly asked the problem and also encourage you to call back again. (The helpline closes at 9:00 pm.)

I was not able to book the token online. In the SRO office they said they entertain on the first come first serve basis. Also they give higher priority to the direct party (as they were calling us) over agents, so your work gets done first. Even though there were a pile of LandL on the SR's desk (the agents use the backdoor before the time beings) he did ours first! We were free in just 20 minutes! So easy! We thanked him and others for their kind co-operation.

At the last minute my friend discovered a mistake in the Public Data Entry details that we had printed, I had already bookmarked the website on my mobile, within a minute we corrected it. Although we couldn't print a new copy of the details, but the digital data was correct which ultimately got reflected in the documents printed by the SRO. 


Please note: The new Public Data Entry website is broken, use the old website which is complete. (as on March 2016)

------------------------------------------------





------------------------------------------------
Getting the basic information about a linux system <a name="20161227-205033"></a>
================================================
* Keywords: linux info, linux management
* Timestamp: 20150701-181811

------------------------------------------------
------------------------------------------------

1. uname -a, uname -snrvmo gives the kernel name, node name, kernel-release, kernel-version, machine arch, operating system

2. For more information also use
    /proc/version
    lsb_release -a      # lsb = Linux Standard Base, provides
                        # distribution specific information.
    /etc/os-release and /etc/lsb-release

------------------------------------------------





------------------------------------------------
Philosophy -- Wikipedia <a name="20161227-205033"></a>
================================================
* Keywords: philisophy, riminet
* Timestamp: 20150701-181811

------------------------------------------------
------------------------------------------------

*Hylozoism - universe is in some sense alive

*prosthetic (prosthetic limb...), comeuppance

*Philosophical topic: At the tip of the blind man's stick.

*Good Quote from Malafouris' book: 'How things shape the mind'

"Mind, as the philosopher Andy Clark notes in his book Being There, 'is a leaky organ, forever escaping its `natural` confines and mingling shamelessly with body and with world' (1997, 53)."


Philosophy is the study of general and fundamental problems, such as those connected with reality, existence, knowledge, values, reason, mind and language.

Etymology: 'philosophia' greek, probably from Pythagoras, meaning 'love for wisdom' or 'friend of wisdom'.

Terms: analytic philosophy(based on reasoning), epistemology -- relationship b/w truth, belief, perception and theories of justification; skepticism, regress argument -- infinitism, foundationalism, coherentism; Munchhausen trilemma, Rationalism vs Empiricism, mental content

*A Cognitive Leakage into the world -- Malafouris

------------------------------------------------





------------------------------------------------
Prof. K.M. Gupt <a name="20161227-205033"></a>
================================================
* Keywords: KM Gupt, vijay vihar
* Timestamp: 20150805-181811

------------------------------------------------
------------------------------------------------

Met Prof. KM Gupt from Materials Dept. He lives on our floor Vijay Vihar

------------------------------------------------


------------------------------------------------
Artificial Intelligence Talk<a name="20161227-205033"></a>
================================================
* Keywords: artificial intelligence tal
* Timestamp: 20150805-181811

------------------------------------------------
------------------------------------------------

Flow of Presentation 

Artificial Intelligence

Man made = Artificial 

What is Intelligence?

The 'what'!?
    - Regress argument
        - Foundationalism
            - base you argument on beliefs
        - Coherentism
            - base your argument on the question (circular argument)
        - Infinitism
            - every justification needs another justification

What matters is YOU!

One way to understand what AI is, is to look back at what caused it?

We go back about 100 years... around the start of 20th Century
    - Formalism: Hilbert and Cantor
    - Russel Paradox
    - Death of the Set Theory
    - Return of the Set Theory
    - Mechanization of Mathematics
    - Principa Mathematica
    - Kurt Godel
    - Allen Turing
    - Turing Test

    Hilbert = Scrooge McDuck
    Cantor = Gyro
    Russell = Launchpad
    Whitehead = Duckworth the butler
    Goldel = Mickey Mouse
    Turing = Donald Duck

John Von Neumann
    - Cellular Automata
    - Conway's Game of Life
    - Discovery of the Glider
    - Gopher's gun!
    - Smallest gun, April 28, 2015
    - Gopher's Gun

------------------------------------------------





------------------------------------------------
personal note <a name="20161227-205033"></a>
================================================
* Keywords: personal note
* Timestamp: 20150928-181511

------------------------------------------------
------------------------------------------------

Life is a puzzle unsolved. I wish to solve it.

The division of today's life into a sequence of five, life, health, skill, relations, money, is quite systematic. I have thought it through consistently.

Life and its philosophy. One's own view point and attitude plays the most important role and hence is the first most important aspect worthy of our attention and time. Here is where I lack the most and hence my condition can be clearly explained. Can the mystery of life be solved? I don't know, after what I know from 30 years of experience. But, I have this feeling that the answer is lying in me, and I am blind enough to be ignorant. The natural question is how to become able of seeing it. How to have a sense of knowing of the truth of life? This infinite craving to know the truth, and having met no one who knows the truth, makes me feel out of sync with the world sometimes. These moments make me deviate from the plan and hence puts my efforts to dust. 

Since the sphere of Life is so confusing, and my constant fixation on this fuzzy and less known thing is unavoidable, the rest of my life becomes fuzzy too. If I can devise a systematic way to tackle it and realign myself towards the goal, I will progress way faster and way higher than now.

Sometimes I think, that solving life is itself a full time job. Doing it with other things is not possible. So why not for a decade concentrate on earning money, and then delve down into the research full-time. With my abilities I can earn a good amount. The main challenge that remains is, how to park the inquisitiveness to know about life for some time and work single mindedly to free myself from the economic and social cycle of the world. 

------------------------------------------------





------------------------------------------------
APS 2016 <a name="20161227-205033"></a>
================================================
* Keywords: meeting with prof uday
* Timestamp: 20151020-122502

------------------------------------------------
------------------------------------------------

    Sir has asked to focus on the APS from now. The goal is to prove to the commitee that
    the PhD topic is worth pursuing and achievable. Focus on creating a good problem
    statement from now on.

    Look at:
    PAG, MELT and semi-rings paper, and search for relevant insights.

------------------------------------------------





------------------------------------------------
Network Management in Ubuntu <a name="20161227-205033"></a>
================================================
* Keywords: network managment, network settings, ubuntu
* Timestamp: 20161227-205033

------------------------------------------------
------------------------------------------------

## Invoking gnome network manager GUI settings editor program
    nm-connection-editor
Also there is the Network Manager Text User Interface program,
    nmtui

## Network Settings using terminal (static ip and gateway)
    ifconfig eth0 10.6.213.20 netmask 255.255.224.0 broadcast 10.6.223.255
    route add default gw 10.6.200.250
Add the DNS `nameserver` to file `/etc/resolv.conf` by appending the line,
    nameserver 10.200.1.11


------------------------------------------------





------------------------------------------------
Network Settings <a name="20161227-205033"></a>
================================================
* Keywords: network settings, home, lab, department
* Timestamp: 20161227-205033

------------------------------------------------
------------------------------------------------

At Type-1 quarter (behind H6):
  address 10.6.213.20
  netmask 255.255.224.0
  gateway 10.6.200.250
  dns-nameserver 10.200.1.11

At GRC Lab (New CSE building):
  address 10.130.41.4
  netmask 255.255.0.0
  gateway 10.130.3.1
  dns-nameserver 10.200.1.11


------------------------------------------------





------------------------------------------------
Setting DNS Server in terminal (Ubuntu) <a name="20161227-205033"></a>
================================================
* Keywords: network settings, home, lab, department
* Timestamp: 20161227-205033

------------------------------------------------
------------------------------------------------

You need to configure the /etc/network/interfaces file if you want to change your DNS server via the command line.

It should look something like this:

# The loopback network interface
    auto lo
    iface lo inet loopback


# The primary network interface
    auto eth0 
    iface eth0 inet static
        address 192.168.X.X
        netmask 255.255.255.0
        gateway 192.168.X.X
        dns-nameservers X.X.X.X 
If you have more than one DNS server, just add a space between each:

dns-nameservers X.X.X.X Y.Y.Y.Y Z.Z.Z.Z
Just replace the X'es with your own IPs and the DNS server of choise, and when this is done, run this command to update the settings:

sudo ifdown eth0 && sudo ifup eth0

------------------------------------------------




------------------------------------------------
Network Ports Service <a name="20161227-205033"></a>
================================================
* Keywords: network ports, ports processes, process ports
* Timestamp: 20161227-205033

------------------------------------------------
------------------------------------------------


/etc/services  -- lists the common ports and standard services that use them

Finding which process is listening on which port:

lsof -i [TCP/UDP]:<port>    # to be run as root, gives processes at specific port

netstat -nlp | grep <port>  # lists all the processes listening on ports once port
                            # is known further info can be found using lsof cmd.


------------------------------------------------





------------------------------------------------
Downloading a offline copy of website <a name="20161213-033841"></a>
================================================
* Keywords: wget, web management
* Timestamp: 20161213-033841

------------------------------------------------
------------------------------------------------

    wget --mirror --convert-links --adjust-extension --page-requisites --no-parent -w 1 http://example.org

    --mirror – Makes (among other things) the download recursive.
    --convert-links – convert all the links (also to stuff like CSS stylesheets) to relative, so it will be suitable for offline viewing.
    --adjust-extension – Adds suitable extensions to filenames (html or css) depending on their content-type.
    --page-requisites – Download things like CSS style-sheets and images required to properly display the page offline.
    --no-parent – When recursing do not ascend to the parent directory. It useful for restricting the download to only a portion of the site.
    -w 1 -- pauses for 1 second between each request so that the firewall doesn't suspect/ you don't bombard the site.

------------------------------------------------





------------------------------------------------
Lenovo ideapad 100 14IBY <a name="20161213-033841"></a>
================================================
* Keywords: lenovo drivers
* Timestamp: 20161213-033841

------------------------------------------------
------------------------------------------------

Drivers link:
http://support.lenovo.com/in/en/products/laptops-and-netbooks/100-series/100-14iby?beta=false

------------------------------------------------





------------------------------------------------
Nautilus Settings <a name="20161213-033841"></a>
================================================
* Keywords: file browser, ubuntu, gnome
* Timestamp: 20161213-033841

------------------------------------------------
------------------------------------------------
Settings tested on "GNOME nautilus 3.14.3".

##Changing default editor to vim

1. Goto /usr/share/applications/ and check if vim.desktop exists (if not create one by referring other .desktop files)
2. Goto /etc/gnome/defaults.list and change all occurances of gedit.desktop to vim.desktop
3. Now things should work, if not, then logout and login.
4. For other type of files either edit /etc/gnome/defaults.list against proper MIME type or set defaults using Nautilus gui.

##Adding Scripts

1. Goto script folder: ~/.local/share/nautilus/scripts/
2. Create an *executable* script.
3. Open `nautilus` and right click on a file/folder and script name should be showing in the 'Scripts' submenu.

There are some environment variables availabe to the scripts called from `nautilus`:

* `NAUTILUS_SCRIPT_SELECTED_FILE_PATHS` : newline-delimited paths for selected files (only if local) 

* `NAUTILUS_SCRIPT_SELECTED_URIS` : newline-delimited URIs for selected files 

* `NAUTILUS_SCRIPT_CURRENT_URI` : current location 

* `NAUTILUS_SCRIPT_WINDOW_GEOMETRY` : position and size of current window 


##Adding a terminal opening shortcut

1. In the scripts folder : ~/.local/share/nautilus/scripts/ create an executable script that opens up a terminal. The contents of the script can be as given (assuming script-name 'terminal'):

        #!/bin/sh
        gnome-terminal

2. Logout and login again.
3. Open the file ~/.config/nautilus/accels and you would see many lines starting with a semicolon. Find the line like this:

        ; (gtk_accel_path "<Actions>/ScriptsGroup/script_file:\\s\\s\\shome\\scodeman\\s.local\\sshare\\snautilus\\sscripts\\sterminal" "")

   Note that this line is automatically generated when you logout and login (provided you have made the script file 'terminal', put it in the right place, and made it executable). Leading semicolon makes this line a comment, hence remove it. And add the shortcut F4 into the last pair of double quotes. Changed line would look like this:

        (gtk_accel_path "<Actions>/ScriptsGroup/script_file:\\s\\s\\shome\\scodeman\\s.local\\sshare\\snautilus\\sscripts\\sterminal" "F4")

4. Now test the shortcut, if it doesnot work, try logout and login again.

------------------------------------------------





------------------------------------------------
Markdown (.md files) <a name="20161213-041904"></a>
================================================
* Keywords: markdown, html
* Timestamp: 20161213-041904
* [Good Resource 1](https://daringfireball.net/projects/markdown/syntax)

------------------------------------------------
------------------------------------------------

##Compiling

* Install the program with `sudo apt-get install markdown`
* Now use it : `markdown filename.md > filename.html`

##Philosophy

Markdown has been basically inspired from text-emails. Its tries to be as close to a readable document as possible. Other tools similar to `markdown` have inspired its layout.

##Important Points

* These notes are in markdown.
* To add same-document cross references, mark the place with `<a name="abcd"></a>`. And refer to it with `[link](#abcd)`.

------------------------------------------------





------------------------------------------------
Filesystem sharing using Samba <a name="20161216-190516"></a>
================================================
* Keywords: samba file sharing, file management, data management, central repository
* Timestamp: 20161216-190516

------------------------------------------------
------------------------------------------------

1. Install Samba
        sudo apt-get update
        sudo apt-get install samba
2. Create a samba user and set its password.
        sudo smbpasswd -a <user-name>
<br/>
        Samba uses separate set of passwords than the system. Therefore, to remember use your system password again.
<br/>
        The <user-name> chosen should already exist. And the location intended to be shared must be accessibe to the user.
<br/>

3. Save a copy of `/etc/samba/smb.conf` somewhere to restore `smb.conf` in case you wrongly edit it.

4. Edit `/etc/samba/smb.conf` and append the following at the end: (one entry for each folder shared)

        [<folder_name>]
        path = /home/<user_name>/<folder_name>
        valid users = <user_name>
        read only = no
5. Restart Samba service.
        sudo service smbd restart

6. Check `smb.conf` for any syntax errors. Run the following command.
        testparm

7. Test the samba server
        sudo apt-get install smbclient
        # List all shares:
        smbclient -L //<HOST_IP_OR_NAME>/<folder_name> -U <user>
        # connect:
        smbclient //<HOST_IP_OR_NAME>/<folder_name> -U <user>

8. Open samba share in nautilus file browser. Go to the address bar and type `smb://<host>/[<directory>]


------------------------------------------------





------------------------------------------------
Python3 Date Time <a name="20161225-234823"></a>
================================================
* Keywords: datetime, DateTime, python3 datetime , time
* Timestamp: 20161225-234823

------------------------------------------------
------------------------------------------------

## import time

* `time.sleep(5)` : sleep for 5 seconds
* `time.sleep(0.5)` : sleep for 0.5 seconds

## from datetime import datetime as dt

* `dtf = "%Y%m%d-%H%M%S"` : a standard datetime format
* `dt.now()` : returns a datetime.datetime object
* `dt.now().strftime(dtf)` : return a string in format `YYYYMMDD-HHMMSS`
* `dt.strptime("20161225-234823", dtf)` : returns a datetime object initialized from the string in format

## from datetime import datetime as dt, timedelta as td

* `tdo = td(days=2, seconds=3600)` : create a timedelta object
* `dt.now() + tdo` : add timedelta to datetime object
* `dt.now() - (dt.now() - tdo)` : will be very close to the value of `tdo` object (defined above)

------------------------------------------------





------------------------------------------------
Python3 Threading <a name="20161225-234823"></a>
================================================
* Keywords: multithreading, python3, threading module
* Timestamp: 20161225-234823

------------------------------------------------
------------------------------------------------

* A simple example:
        import time
        from threading import Thread

        class worker(Thread):
            def run(self):
                for x in xrange(0,11):
                    print x
                    time.sleep(1) # for one second

        class waiter(Thread):
            def run(self):
                for x in xrange(100,103):
                    print x
                    time.sleep(5)

        if __name__ == "__main__":
            worker().start()
            waiter().start()

* `threading.Thread(target=run, kwargs=dict(host='localhost', port=8080)).start()` : call a function named `run` by passing it arguments, in a new thread.

* A simple reader and writer:

        #!/usr/bin/env python3
        from threading import Thread
        from queue import Queue, Empty
        import time


        sharedq = Queue()
        limit = 100

        def writer():
            for i in range(limit):
                sharedq.put(i)
                time.sleep(1) # sleep for n second

        def reader():
            for i in range(limit):
                try:
                    val = sharedq.get(timeout=.5) # wait till 5 seconds to get value
                except Empty:
                    # Empty exception raised if Queue is empty
                    print("Nothing in Queue")
                else:
                    print("Received Val:", val)

        if __name__ == "__main__":
            Thread(target=writer, kwargs={}).start()
            Thread(target=reader, kwargs={}).start()

------------------------------------------------





------------------------------------------------
Sqlite3 usage<a name="20161226-022225"></a>
================================================
* Keywords: sqlite3, sql, sqlite3 bash command
* Timestamp: 20161226-022225

------------------------------------------------
------------------------------------------------

## sqlite3 bash usage

* `sqlite3 [db-file-name]` : opens up the sqlite3 database
* `> .read FILENAME` : execute sql in FILENAME
* `> .schema ?TABEL?` : show CREATE statements
* `> .dump ?TABLE?` : dump the database in an SQL text format. If TABLE specified, only dump tables matching LIKE pattern TABLE.
* `> .save FILE` : Write in-memory database in FILE
* `> .quit` : exit this program

## sql in sqlite3

* kk

------------------------------------------------




------------------------------------------------
Boot Repair <a name="20170111-153223"></a>
================================================
* Keywords: boot repair, ubuntu software
* Timestamp: 20170111-153223

------------------------------------------------
------------------------------------------------
sudo add-apt-repository ppa:yannubuntu/boot-repair
sudo apt-get update
sudo apt-get install -y boot-repair && boot-repair


------------------------------------------------





------------------------------------------------
Ubuntu Software List <a name="20170111-153223"></a>
================================================
* Keywords: ubuntu software list, essential ubuntu software packages, ubuntu packages list, ubuntu package list, important ubuntu, ubuntu programs, ubuntu multimedia programs, ubuntu utility, ubuntu package management, ubuntu networking, ubuntu internet, ubuntu office, wps office, ubnuntu development
* Timestamp: 20170111-153223

------------------------------------------------
------------------------------------------------

These are package names that can be used directly in the command `sudo apt install <package-name>` command, unless stated otherwise.

* Multimedia (multimedia programs)
    * shotwell
    * gimp (image editor)
    * vlc
    * audacity (audio editor)
    * jpegoptim
    * imagemagick (contains programs like `convert`)
    * video editors
        * openshot (free)
        * kdenlive (free)
        * flowblade movie editor
        * lightworks
        * blender
        * ffmpeg (mpeg compressing/altering tool)

* Utility
    * guake (quick desktop terminal shortcut F12)
    * terminator (a multiwindow terminal)
    * unity-tweak-tool
    * indicator-cpufreq (view and control cpu frequency from top-panel)
    * indicator-multiload (view system resource stats on top-panel)
    * ubuntu-restricted-extra (mp3 codec and other proprietary softwares)
    * qtqr (in ppa:qr-tools-developers/qr-tools-stable) (A QR code reader - from image files and webcam)
    * xrandr-invert-colors (https://github.com/zoltanp/xrandr-invert-colors.git)

* Package Management Tools (not available by default)
    * dlocate (locates packages containing a given file)
    * apt-file (a tool like dlocate)

* Internet
    * links (command line browser)
    * google-chrome (download directly from google)
    * uget (download manager)
    * linuxdcpp

* System
    * tlp and tlp-rdw (after installation `sudo tlp start`)
    * preload (preloads frequently used programs but cosumes ram)
    * gparted (disk patition management)

* Development
    * clang (implies clang/llvm)
    * python3-pip (for pip3)
    * virtualenv (virtual env creator for python)
    * default-jdk (openjdk gives error on install)
    * vim-gtk3-py2 (py2 because of youcompleteme)
    * git
    * subversion (i.e. svn)

* Office and documents
    * WPS Office (wps office : download from [here](http://wps-community.org/downloads))
    * texlive-full
    * texmaker
    * freeplane (a replacement for freemind)
    * okular (more featured pdf reader -- just-in-case)


------------------------------------------------





------------------------------------------------
Linux RAM Disk <a name="20170112-010422"></a>
================================================
* Keywords: linux ram disk, file management, filesystem on ram, ram filesystem
* Timestamp: 20170112-010422

------------------------------------------------
------------------------------------------------
Creating an 800MB ram disk (tested on Ubuntu): (8192=8M)
    $ sudo mkfs -t ext2 -q /dev/ram1 819200
    $ sudo mkdir -p /media/ramcache
    $ sudo mount /dev/ram1 /ramcache # mount the partition
    $ sudo df -H | grep ramcache

------------------------------------------------





------------------------------------------------
Compiler Optimizations <a name="20170123-221735"></a>
================================================
* Keywords: compiler optimizations website, span
* Timestamp: 20170123-221735

------------------------------------------------
------------------------------------------------

A good website
http://www.compileroptimizations.com/

------------------------------------------------





------------------------------------------------
Horizontal Scrolling <a name="20170131-134219"></a>
================================================
* Keywords: horizontal scrolling, scrolling ubuntu 16.04, scrolling management
* Timestamp: 20170131-134219

------------------------------------------------
------------------------------------------------
    To be able to set these settings through Terminal or through the gnome-control-center you need to make sure that you have xserver-xorg-input-libinput installed. It appears to be a bug that it is not already installed by default, in order to install simply run:

    sudo apt-get install xserver-xorg-input-libinput libinput10

    sudo rm /uar/share/X11/xorg.conf.d/*synaptic*
    sudo apt-get remove xserver-xorg-input-synaptics

    After doing so and then logging out and in again you will find new settings in the gnome-control-center's Mouse & Touchpad settings:

    # gsettings set org.gnome.settings-daemon.peripherals.touchpad horiz-scroll-enabled "true"

    # synclient HorizEdgeScroll=1
    # xinput is another command

    # I enabled tapping on my touchpad (id:12, id can change on reboot)
    xinput set-prop 12 "libinput Tapping Enabled" 1

------------------------------------------------





------------------------------------------------
Default C/CPP compiler <a name="20170404-162559"></a>
================================================
* Keywords: c++, default c++, c and cc management
* Timestamp: 20170404-162559

------------------------------------------------
------------------------------------------------

the `cc` and `c++` commands in Ubuntu are symlinks to the default C and CPP compiler. Many tools (like cmake) read these symlinks to find the default comiler. Here is how to update them:

By default (on my system):
    `/usr/bin/cc --> /etc/alternatives/cc --> /usr/bin/gcc`

    `/usr/bin/c++ --> /etc/alternatives/c++ --> /usr/bin/gcc++`


* cpp
        sudo update-alternatives --config c++

* c
        sudo update-alternatives --config cc


------------------------------------------------





------------------------------------------------
Grub <a name="20170411-134530"></a>
================================================
* Keywords: grub 2, grub rescue, grub 2 rescue, non booting, grub management
* Timestamp: 20170411-134530

------------------------------------------------
------------------------------------------------

Used these commands on Priyanka's laptop and got to the grub menu:

    grub rescue> set prefix=(hd0,gpt6)/boot/grub
    grub rescue> set root=(hd0,gpt6)
    grub rescue> insmod normal
    grub rescue> normal

* [Ref1](https://www.linux.com/learn/how-rescue-non-booting-grub-2-linux)

------------------------------------------------





------------------------------------------------
Linux Memory and its Testing <a name="linux-memory"></a>
================================================
* Keywords: linux hardware information, linux, ubuntu, memory info, memory testing, linux resource information, memory management
* Timestamp: 20170420-095108

------------------------------------------------
------------------------------------------------

Getting hardware info on Memory (likewise others too) in Linux:

* Using `lshw` command

        $ sudo lshw -C memory

  Here `-C` represents the class of hardware.

* Using `hardinfo`

        $ sudo apt-get install hardinfo
        $ hardinfo

* Using `memtester`

        $ sudo apt-get install memtester
        $ sudo memtester 4G 2

  The command `memtester 4G 1` tests 4GB of user space memory `2` times. It needs to be run as `sudo` since it needs to **lock** the given amount of memory.

* Using `mbw` : Memory BandWidth benchmark

        $ sudo apt-get install mbw
        $ mbw -n 4 100

  The command `mbw -n 4 100` calculates the system memory bandwidth by repeating each test on 100MB four times.

------------------------------------------------





------------------------------------------------
Linux dcpp hubs iitb <a name="20170501-164621"></a>
================================================
* Keywords: dcpp hubs, dc plus plus iitb hubs
* Timestamp: 20170501-164621

------------------------------------------------
------------------------------------------------

iitbdcpphubs.weebly.com
10.105.177.8:411  (The Hub)
10.107.2.55:411   (EvilKagawa)
10.14.32.32:411   (The\_Champion)
10.14.32.32:412   (The\_Champion)
10.14.32.32:1209  (The\_Champion)

------------------------------------------------





------------------------------------------------
Ubuntu using Intel Graphics Card <a name="20170505-215046"></a>
================================================
* Keywords: intel graphics card, ubuntu graphics support
* Timestamp: 20170505-215046

------------------------------------------------
------------------------------------------------

Use the `unity_support_test`, and the answer should be yes as given below:

    >>PROMPT(19, 2016, 00:51:57) 
    codeman@nintel05: boot $ /usr/lib/nux/unity_support_test -p
    OpenGL vendor string:   Intel Open Source Technology Center
    OpenGL renderer string: Mesa DRI Intel(R) HD Graphics 5500 (Broadwell GT2) 
    OpenGL version string:  3.0 Mesa 12.0.6

    Not software rendered:    yes
    Not blacklisted:          yes
    GLX fbconfig:             yes
    GLX texture from pixmap:  yes
    GL npot or rect textures: yes
    GL vertex program:        yes
    GL fragment program:      yes
    GL vertex buffer object:  yes
    GL framebuffer object:    yes
    GL version is 1.4+:       yes

    Unity 3D supported:       yes

------------------------------------------------





------------------------------------------------
learn linux main <a name="20170506-015158"></a> 
================================================
* Keywords: learning linux, linux resources, learn linux, learn ubuntu, learning ubuntu, learn ubuntu, ubuntu management, linux management, linux administration, ubuntu administration, linux skills, ubuntu skills, linux commands main
* Timestamp: 20170506-015158

------------------------------------------------
------------------------------------------------

Important Categories of System Management Tasks
-----------------------------------

* user and group management (search user management here)
* package management
* linux installation
* grub tweaking
* process management - and systemd, systemctl
* file and filesystem management (ext2,3,4)
* working with terminal (shell scripts, commands, text filtering)
* manage system resources (get their basic information and current state of important resources)
* assess and evaluate the health of the system
* configuring and playing with network interface and settings
* x window system and display managers
* vim editor
* python shell scripting
* tweaking the kernel parameters for specific usecases
* nginx


systemd on linux/ubuntu
----------------------
1. [howtogeek.com](https://www.howtogeek.com/216454/how-to-manage-systemd-services-on-a-linux-system/)
2. [linux.com](https://www.linux.com/learn/here-we-go-again-another-linux-init-intro-systemd)

grub2 on linux/ubuntu
----------------------
1. [dedoimedo.com]( http://www.dedoimedo.com/computers/grub-2.html)

useful linux commands/softwares
----------------------
1. [Highly useful commands](http://www.dedoimedo.com/computers/linux_commands.html)
2. [Best linux softwares](http://www.dedoimedo.com/computers/linux-best-software-2012.html#mozTocId457900)

using lsof
-----------------
1. [10 lsof command examples](https://www.tecmint.com/10-lsof-command-examples-in-linux/)
2. [15 lsof command examples](http://www.thegeekstuff.com/2012/08/lsof-command-examples)

information of hardware
----------------------------
1. [16 commands to check hardware information](http://www.binarytides.com/linux-commands-hardware-info/)
2. [Getting h/w info using lshw](http://www.binarytides.com/linux-lshw-command/)


------------------------------------------------





------------------------------------------------
Hardware Information in Linux <a name="20170511-235928"></a>
================================================
* Keywords: hardware information in linux, linux hardware info, hard info, hw management
* Timestamp: 20170511-235928

------------------------------------------------
------------------------------------------------

Some Good Resources
------------------
* <http://www.binarytides.com/linux-commands-hardware-info/>
* <http://www.binarytides.com/linux-hwinfo-command/>
* <http://www.binarytides.com/linux-lshw-command/>

The commands (most important first)
---------------
* `hwinfo`
* `sudo dmidecode`
* `hardinfo` (gui based detailed info)
* ls commands
  * `lshw`
  * `lscpu`
  * `lspci`
  * `lsblk` (block devices)
  * `lsscsi`
  * `lsusb`
* proc files
  * `/proc/cpuinfo`
  * `/proc/meminfo`
  * `/proc/version` (linux version)
  * `/proc/scsi/scsi` (scsi/sata devices)
  * `/proc/partitions`
* othes
  * `hdparm -i /dev/sda` (info on storage /dev/sda)
  * `pydf` (a pleasant version of `df`)
  * `df`
  * `fdisk`
  * `mount | column -t`
  * `free`

Device Specific Information
----------------------------
1. CPU
   * `lscpu`
   * `cat /proc/cpuinfo`
   * `sudo dmidecode -t processor`
   * `sudo dmidecode -t cache`
   * `hwinfo --cpu`
   * `hardinfo` (gui based, detailed and easy info)
2. Memory
   * `free -m`
   * `cat /proc/meminfo`
   * `sudo dmidecode -t memory`
   * `sudo dmidecode -t 16` (info on pysical memory array)
   * `sudo dmidecode -t 17` (info on memory devices)
   * `sudo lshw -C memory`
3. Others
   * `hwinfo --keyboard --short`
   * `hwinfo --mouse --short`
   * `hwinfo --monitor --short`
   * `hwinfo --disk --short`
   * `hwinfo --usb --short`
   * `hwinfo --network --short`


------------------------------------------------





------------------------------------------------
GRC Lab New Desktop Specs <a name="20170515-114344"></a>
================================================
* Keywords: grc new desktop specs, specifications
* Timestamp: 20170515-114344

------------------------------------------------
------------------------------------------------

New Desktop with following specifications:

1. Intel Core i7-7700K Processor
2. ASUS PRIME Z270-A (Obsolete: Gigabyte GA-B250M-DS3H Motherboard)
3. SMPS and Chasis for the above Motheboard
4. 64GB (4x16GB) DDR4 RAM @2400MHz
5. Primary SSD   : Kingston SSDNow UV400 240GB SATA 3 2.5" Solid State Drive (SUV400S37/240G)
6. Secondary HDD : 2 TB Internal Desktop HDD 7200RPM
7. CD/DVD Writer
8. Monitor (>=24") (optional)
9. Keyboard and Mouse


------------------------------------------------





------------------------------------------------
Compress Videos <a name="20170715-191559"></a>
================================================
* Keywords: linux compress videos, video compression, ubuntu video compression, ffmpeg, crf, constant rate factor, mp4 compression
* Timestamp: 20170715-191559

------------------------------------------------
------------------------------------------------

Use `ffmpeg` program.

There are two basic encoders x264 and x265. We use CRF (Constant Rate Factor) in x264 and x265 for conversion.

For x264, sane values are between 18 and 28. The default is 23, so you can use this as a starting point.

With ffmpeg, it’d look like this:

    ffmpeg -i input.mp4 -c:v libx264 -crf 23 output.mp4

For x265, the default CRF is 28:

    ffmpeg -i input.mp4 -c:v libx265 -crf 28 output.mp4

[1]: http://slhck.info/video/2017/02/24/crf-guide.html

------------------------------------------------





------------------------------------------------
File Management <a name="20170722-105331"></a>
================================================
* Keywords: ubuntu file management, ubuntu filesystem management, linux file management, linux filesystem management
* Timestamp: 20170722-105331

------------------------------------------------
------------------------------------------------

* the useful programs:
    * `du` `df`
    * `pv`
    * `ls` `tree`
    * `chmod` `chown`
    * `mkdir`
    * `touch`
    * `cp` `mv`
    * `rm` `rmdir`

* Getting only size of a file in bytes: (use this instead of `ls` because the output of `ls` is not standard)

        du -b $filename | cut -f1

------------------------------------------------





------------------------------------------------
SPAN Quick Notes <a name="20170724-132955"></a>
================================================
* Keywords: phd research, compiler research, span quick notes, synergistic program analysis
* Timestamp: 20170724-132955

------------------------------------------------
------------------------------------------------

SpecDFA Link
-------------------
https://www.cse.iitb.ac.in/~uday/sdfa-web

Quick Notes on SPA
-------------------

* Practical Cases vs Possible Cases : Always keep in mind and distinguish between these cases. Work hard to make the analysis give good results in practical cases and ammend the analysis to give sound result in possible cases. E.g. Practically, a loop only exits from its body, and there is no jump directly into the middle of the loop. But it is possible to jump straight into the body of the loop from other places in the program (although it does't make sense but possible).


------------------------------------------------





------------------------------------------------
Python Notes <a name="20170730-164721"></a>
================================================
* Keywords: learn python, python 3 notes, python notes, python programming language, python3 skills, python skills
* Timestamp: 20170730-164721

------------------------------------------------
------------------------------------------------

1. Basic data types, their literal representation, conversion, and operations on them.

2. Top level elements of a complete Python Project. (package, module, function, class, decorator, other python stmts)

3. Flow control statements (for-in, while, if-elif-else, if-else-ternary, yield, yield-from, break, continue, return, function call)

4. Operators and Keywords

   Keywords:

        False      class      finally    is         return
        None       continue   for        lambda     try
        True       def        from       nonlocal   while
        and        del        global     not        with
        as         elif       if         or         yield
        assert     else       import     pass
        break      except     in         raise

5. Namespace and scoping
    * Scope rules: [Reference][LEGBstackoverflow], LEGB (Local, Enclosing, Global, Builtins)
    * List comprehensions, dict and set comprehensions have their own scope
    * Generator expression have their own scope
    * attribute access lookup logic (`__mro__`)

    [LEGBstackoverflow]: https://stackoverflow.com/questions/291978/short-description-of-the-scoping-rules/23471004#23471004

6. Class, class object, class' object/instance

7. Special Objects: object, module, type, method, function

8. Special variables and functions (attributes) for packages, modules, functions, classes, objects, methods

9. Memory Model of python programs (reference counting, stack): CPython virtual machine is stack based

10. Useful concepts
    1. List comprehension and generator expressions (gen. exprs save memory)
    2. Generator functions (yield)
    3. Decorators (@property etc..) : higher order functions
    4. Descriptor Pattern (property, staticmethod, classmethod)
    5. Method vs Function (`method.__self__`, `method.__func__`)
    6. Context Manager (`with`, `__enter__`, `__exit__`)

11. Data Structures and operations on/between them.
    1. str (io.StringIO)
    2. bytes (bytearray, io.BytesIO)
    3. tuple (collections.namedtuple)
    4. list (as array and stack) (map, filter, zip, list comprehension)
    5. dict
    6. set
    7. collections.deque (as queue, doubly ended queue, circular queue: deque(maxlen=N))
    8. heapq module (heap implemented on/using list)
    9. Threading: queue.Queue
    10. Threading: queue.PriorityQueue

12. Basic Standard Library Usage
    0. builtins
        * abs, round
        * bool, int, float, str, bytes, bytearray
        * chr, ord, repr
        * tuple, list, dict, set, frozenset
        * len, max, min, sum, all, any
        * sorted, enumerate
        * reversed
        * range
        * print, open
    1. re
        * compile, match, search, findall, sub, split
    2. random
        * randint, random, choice, shuffle
    3. math
        * ceil, floor
        * pi
    4. os
        * environ
        * sep (altsep), extsep, pathsep, linesep
        * getcwd, chdir, listdir
    5. os.path
        * split, basename, dirname, realpath, splitext, join
        * abspath, relpath, realpath, normpath, expanduser, expandvars
        * isabs, exists, isfile, isdir, islink, ismount
        * getatime, getctime, getmtime, getsize
    6. subprocess
        * run, returncode, getoutput, getstatusoutput
        * `p = subprocess.run("ls", shell=True)`
        * -- command can be any script understood by /bin/sh
        * -- pipes, io redirections can be used
        * -- use 2>&1 and /dev/null to discard output
        * -- how to use /bin/bash instead of /bin/sh ?
    7. sys
        * args
        * stdin, stdout, stderr, `__stdin__`, `__stdout__`, `__stderr__`
        * path, modules
        * version
        * getrecursionlimit, setrecursionlimit
        * getsizeof
        * ps1, ps2, platform, byteorder
    8. string
        * ascii_letters, ascii_lowercase, ascii_uppercase
        * digits, hexdigits, octdigits
        * printable, punctuation, whitespace
    9. struct
        * pack, unpack
        * bigEndian (!, >), littleEndian (<)
        * -- integers: bB hH iI qQ
        * -- floats: f d
    10. json
    11. csv
    12. xml
    13. base64
    14. timeit
    15. time
        * sleep
    16. datetime
    17. doctest, unittest
        * `python3 -m doctest <filename>`
        * -- doctest: `...` and <BLANKLINE>
    18. io
        * open, BytesIO, StringIO, getvalue()
    19. shlex
        * split
    20. textwrap
        * dedent
    21. copy
        * copy, deepcopy

13. Threading and communication. (TODO)

14. Related: assert keyword, __debug__ vaiable, -O cmd option

* C3 linearization (Method Resolution Order) : `Class.__mro__` or `ClassObj.mro()`
* Descriptor Pattern (`__get__`, `__set__`, `__delete__`)

------------------------------------------------





------------------------------------------------
Ubuntu Commands <a name="20170804-185150"></a>
================================================
* Keywords: ubuntu commands, ubuntu bash, bash commands, linux commands
* Timestamp: 20170804-185150

------------------------------------------------
------------------------------------------------

* Networking related (network commands)
    * Set static ip for interface eth0 in `/etc/network/interfaces`

            # This file describes the network interfaces available on your system
            # and how to activate them. For more information, see interfaces(5).

            # The loopback network interface
            auto lo
            iface lo inet loopback

            # The primary network interface
            auto eth0
            iface eth0 inet static
                address 10.0.0.41
                netmask 255.255.255.0
                network 10.0.0.0
                broadcast 10.0.0.255
                gateway 10.0.0.1
                dns-nameservers 10.0.0.1 8.8.8.8
                dns-domain acme.com
                dns-search acme.com

    * For DHCP the entry in `/etc/network/interfaces` should be:

            auto eth0
            iface eth0 inet dhcp

    * `lshw -C network` -- lists network interfaces with relevant info
    * lspci -- lists all hardware, grep to find the device.
    * ifconfig
        * `ifconfig eth0 192.168.1.3 netmask 255.255.255.0 broadcast 192.168.1 255`
        * `ifconfig eth0 up`
        * `ifconfig eth0 down`
    * netstat
    * route
        * `route add default gw <IP_ADDRESS> <INTERFACE_NAME>`
    * `/etc/hostname` -- hostname of the system
    * `/etc/hosts` -- static table lookup for hostnames

* process commands

    * `ps -C <process-name> -o pid=` prints only the pid of the given process name.
    * `ps aux | grep <process-name-regex>` prints the pid along with other info for the matched process names.
    * `sudo lsof -p <pid>` prints the open files of the given process
    * `sudo lsof -i :<port>` prints the established connections on the given port.
    * `sudo netstat -nlp | grep <process-name-regex>` shows any sockets (IP:Port) used by the matched processes
    * `sudo netstat -nlp | grep :<port>` shows any process using the specific port.

------------------------------------------------





------------------------------------------------
Ubuntu 16 WiFi Drops <a name="20170810-123519"></a>
================================================
* Keywords: wifi drops, wifi disconnects, ubuntu 16 wifi, ubuntu16 wifi
* Timestamp: 20170810-123519

------------------------------------------------
------------------------------------------------

Found solution [here](https://ubuntuforums.org/showthread.php?t=2348161) in threads #4, #10 and #6.

Ran the following commands and the wifi problem was solved:

    sudo apt-get install --reinstall linux-firmware

    # disable power saving option
    echo "options rtl8821ae fwlps=N" | sudo tee -a /etc/modprobe.d/rtl8821ae.conf

    # stop network manager from enabling power saving
    sudo sed -i 's/wifi.powersave = 3/wifi.powersave = 2/' /etc/NetworkManager/conf.d/default-wifi-powersave-on.conf
    reboot

    # repeat the below process for any change in kernel version
    git clone https://github.com/lwfinger/rtlwifi_new.git
    cd rtlwifi_new
    make
    sudo make install
    reboot

    # to recompile and install the above package for another kernel
    cd rtlwifi_new
    make clean
    make
    sudo make install
    reboot


------------------------------------------------





------------------------------------------------
Program Analysis Notes <a name="20170814-102651"></a>
================================================
* Keywords: program analysis notes, data flow analysis, compilers, languages
* Timestamp: 20170814-102651

------------------------------------------------
------------------------------------------------

###Q. Why program analysis?
We use program analysis majorly for **program optimization** and in evaluating **program correctness**.
Other areas include, **program verification** (which consumes *correctness* too). Program analysis is also used for
machine code generation (for example liveness information for the register allocation of variables).

* The way I have learned to categorize and learn things,
    * Mathematical concepts (Lattice, Descending Chain Condition (DCC), Jacobi Method, Fixed Points (MoFP, MoP, MFP), Complexity)
    * Various analyses and their implementaion (intra and inter-procedural)
    * Typical approaches to the following proofs,
        * Monotonicity
        * Termination
        * Soundness
        * Precision
        * Complexity (Time & Space)
    * Other concepts and techniques
        * Inter-procedural techniques
        * Summary flow functions
        * Demand driven techniques
    * Related
        * Control flow analysis
        * Data dependence analysis
        * Program Verification

* Terms
    * Sparse Loop vs Dense Loop vs Semi-Dense Loop
    * Affine vs Linear: f(x) = 2x is linear and affine; f(x)=2x+3 is affine.
      Linear: f(ax) + f(bx)  = f(ax + bx)
      Affine: f(ax) + f(bx) != f(ax + bx)
      An affine function is the composition of a linear function followed by a translation.
    * Translation Unit (LLVM term is Module)
    * Top-Down and Bottom-Up VS. Forward and Backward
    * Flow Sensitive vs Flow Insensitive
    * Context Sensitive vs Context Insensitive vs Context Independent
    * Over-Approximation vs Under-Approximation ??
    * Program/Control Flow Path
    * Program/Control Flow Point


------------------------------------------------





------------------------------------------------
Self Improvement Notes <a name="20170817-220918"></a>
================================================
* Keywords: quotes, self improvement, motivational
* Timestamp: 20170817-220918

------------------------------------------------
------------------------------------------------

* Law of Attraction -- The Secret

* Thoughts become things. -- The Secret

* "Every thought of yours is a real thing -- a force" - Prentice Mulford (1834-1891)

* "I am the master of my thoughts." -- The Secret

* "Wealth is a mindset" -- The Secret

------------------------------------------------





------------------------------------------------
Spairo <a name="20170924-171008"></a>
================================================
* Keywords: sparc ajit project, sparc project
* Timestamp: 20170924-171008

------------------------------------------------
------------------------------------------------
nasima kazi 4713

Benchmarks:
  whetstone benchmark
  dotproduct
  matrix multiply

------------------------------------------------





------------------------------------------------
Creating Debian Packages <a name="20170922-192244"></a>
================================================
* Keywords: creating debian packages, helloworld package
* Timestamp: 20170922-192244

------------------------------------------------
------------------------------------------------

Look in the following folder and read its README.md

/home/codeman/mydata/git/ws/ws-misc-git/deb-packaging/helloworld-pkg

------------------------------------------------





------------------------------------------------
Separating filename from extension in bash <a name="20171023-002314"></a>
================================================
* Keywords: separating filename from extension in bash, bash notes
* Timestamp: 20171023-002314

------------------------------------------------
------------------------------------------------

### Extracting extension and filename from a filename string

    extension="${filename##*.}"

    filenameprefix="${filename%.*}"

### Running a local script on a remote machine,

    ssh root@MachineB 'bash -s' < local_script.sh

------------------------------------------------





------------------------------------------------
IITB Windows 10 key <a name="20171023-234903"></a>
================================================
* Keywords: iitb windows 10 key, windows10 key, Windows10 key
* Timestamp: 20171023-234903

------------------------------------------------
------------------------------------------------

`2G4N2-JV6M6-2CM64-RKTPG-V6DFM`

------------------------------------------------





------------------------------------------------
Similarity of Symbol Names Provides No Certain Information on Code Similarity <a name="20171113-115022"></a>
================================================
* Keywords: sample cocos2d-x games links
* Timestamp: 20171113-115022

------------------------------------------------
------------------------------------------------

https://github.com/MakeSchool/GameOfLife-Cpp
https://github.com/MakeSchool/SushiNeko-Cpp

------------------------------------------------





------------------------------------------------
personal skills main<a name="20171208-184458"></a>
================================================
* Keywords: personal skills, two year plan, 2 year plan, mygoal
* Timestamp: 20171208-184458

------------------------------------------------
------------------------------------------------

In two years time (i.e. before leaving IITB) following are the goals, to be divided into 4 month chunks,

1. (Primary) Two seminal papers in program analysis.
2. (Primary) Knowledge and Experience in computation and related abstract mathematical models.
3. (Primary) LLVM Compiler System contributor. In the analyses domain.
4. (Secondary) Nearly complete *personal* C language compiler. Contribute it in the public domain for educational purposes. Document and tutor it for educational purposes too. Create it using minimal Python language features so that it is easy to follow.
5. (Secondary) Top 10 programming competetion rank.
6. (Secondary) Detailed knowledge of C++, Python, and LLVM IR. Working knowledge of Golang, Haskell, JS, Java, Prolog, x86_64.
7. (Secondary) Ubuntu Administrator and Contributor.
8. (Secondary) Detailed knowledge of data exchange formats/protocols: XML, JSON, CSV, BIBTEX, Image Formats, Video Formats, HTTP(S)
9. (Secondary) Detailed knowledge of: file systems (Ext2,3,4 and ReiserFS)
7. (Tertiary) Share broker to Self and with collaboration.
8. (Tertiary) Good written language skills + 100 books read
9. (Tertiary) Level 2 body fitness. (strength+stamina+flexibility)
10. (Quaternary) Working knowledge of data science and tools.
11. (Quaternary) Active in technical social media (stackoverflow(>2K points), blogs etc.)

Reference: primary, secondary, tertiary, quaternary, quinary, senary, septenary, octonary, nonary, and denary

Self-management tips: <http://www.bizmove.com/skills/m8t.htm>

Detailed Skills
-------------------

* Research
   * Compilers
      * Compiler Theory
      * Discrete Mathematics
      * Automata Theory
      * Data Flow Analysis
      * Compiler Implementation
   * RIMINET

* Qualities
   * Honesty (to yourself)
   * Perceive
   * Patience
   * Persistence
   * Perseverance

* Programming Languages:
   * **c++**
   * java
   * **python3**
   * **javascript**
   * haskell
   * gas for intel/linux
   * golang
   * SQL
   * LLVM IR

* Scripting Languages:
   * bash/zsh
   * make
   * cmake
   * python3
   * vim

* Presentation Languages:
   * markdown
   * latex/beamer/pstricks
   * **html/css/javascript**
   * **dot**
   * **svg**

* Abstractions
   * Trees
   * Graphs
   * Finite State Machine
   * Push Down Automata
   * Turing Machine
   * Lambda Calculus
   * (Partially Ordered) Set/Lattice
   * Software design patterns

* Concepts
   * Tractability
      * Undecidability

* Data Format:
   * [json](http://www.json.org/) (preferred in utf-8 encoding)
   * [csv](https://en.wikipedia.org/wiki/Comma-separated_values)
   * [bibtex](http://www.bibtex.org/)

* Data encoding
   * [url syntax](https://en.wikipedia.org/wiki/URL#Syntax)
   * [base64 (and base64 for urls)](https://en.wikipedia.org/wiki/Base64)

* Tools:
   * git
   * vim
   * clang/llvm
   * linux/debian/ubuntu
   * sqlite3/postgresql
   * data structures and algos
      * list
      * stack
      * queue
      * set
      * hashmap
      * heap

------------------------------------------------





------------------------------------------------
software project managment <a name="20171214-152857"></a>
================================================
* Keywords: project management
* Timestamp: 20171214-152857

------------------------------------------------
------------------------------------------------

software project management
-----------------------------

* git
* make, cmake
* shell and python scripting
* for data: mysql, sqlite3, google sheets, phpmysql
* build details for C++ projects
* working with multimedia files
    * image formats
    * sound formats
    * video formats
* working with latex, dot, markdown, pandoc
* basic diagram/graphic building tools


------------------------------------------------





------------------------------------------------
body fitness goal <a name="20171221-135553"></a>
================================================
* Keywords: body fitness, fitness goal, two year goal, personal health
* Timestamp: 20171221-135553

------------------------------------------------
------------------------------------------------

Each goal level is reached when the set of the listed goals can be done as a *daily routine*. The goals are intentionally not too hard. This is in consideration of the *gilbert syndrome* condition, and something which can be done as a daily routine.

Daily routine for me, with the regular job, is four to five days a week. This is because I am not into body building; I am into personal fitness.

Level 1 Body Fitness
---------------------------

* 4 km continuous jogging
* 50 squats (or 25 squats with 12 kg weight)
* 20 dips
* 10 reps with 6 Kg x 2 weights (TODO: define rep set)
* Do full pikes with ease

Level 2 Body Fitness
---------------------------

* 4 km in 20 minutes
* 10-10 squats on each leg
* 60 dips
* 20 reps with 10 Kg x 2 weights
* Full pikes and 180 degree stretch

------------------------------------------------





------------------------------------------------
linux user management <a name="20180213-164404"></a>
================================================
* Keywords: linux user management
* Timestamp: 20180213-164404

------------------------------------------------
------------------------------------------------

Absolute essential aspects for any user
---------------------------------------
* user name, user id (uid)
* default group name, group id (gid)
* home directory
* login shell
* password

Useful commands:
----------------
* useradd
* usermod
* userdel
* groupadd
* groupmod
* groupdel

Important Files/Directories
---------------------------
* /etc/passwd
* /etc/group
* /etc/shadow
* /etc/default/useradd
* /etc/login.defs
* /etc/skel (default contents for home dir)

------------------------------------------------





------------------------------------------------
Linux Commands and Files <a name="20180325-235306"></a>
================================================
* Keywords: ubuntu commands and files, linux commands, linux files, ubuntu files, ubuntu resource, linux recources
* Timestamp: 20180325-235306

------------------------------------------------
------------------------------------------------

Categorized commands
--------------------

* environment variables
        
        /etc/environment
        /etc/profile
        /etc/profile.d/
        ~/.profile
        ~/.zshrc
        ~/.bashrc

* process management

        pgrep
        pkill
        pstree
        sudo killall
        sudo kill
        pwdx
        lsof
        sudo netstat -tulpn
        nohup
        nice
        renice
        ctrl-z
        bg
        fg
        jobs

* GRUB2 management
* systemd, systemctl and journalctl
* system logs
* hardware management
* file and filesystem management

* user management
* network management
* package management
* cron jobs
 
* fonts management
* printer management
* nautilus management
* git management
* zsh management
* vim management
* gnome management

* llvm management
* library management (.so, .a)
* clion management

* samba management
* postgre management
* nginx management
* firefox management
* django management
* pycharm management
* docker management

* json management
* csv management

------------------------------------------------





------------------------------------------------
clang static analyzer <a name="20180626-171325"></a>
================================================
* Keywords: adding a new clang static analyzer
* Timestamp: 20180626-171325

------------------------------------------------
------------------------------------------------

Created a copy of LiveVariables:
Files affected: use `locate` to find all these files
1. MyLiveVariables.cpp
2. MyLiveVariables.h
3. Checkers.td
4. DebugCheckers.cpp
5. CMakeLists.txt : added MyLiveVariables.cpp file name after to the LiveVariables.cpp file.

After making all the changes go to the `build/` directory and invoke `ninja` or `make` depending on the build system cmake was initially targetted for.

Almost every personal change or tweak is marked with special single line comment beginning with `//AD`.


------------------------------------------------





------------------------------------------------
mail to uday sir <a name="20180707-124528"></a>
================================================
* Keywords: email to uday sir
* Timestamp: 20180707-124528

------------------------------------------------
------------------------------------------------

Dear Sir,

It seems I am unable to rest without thinking about the research problem constantly. Hence, I inadvertently took this time to mull over the larger problem, its goals and our approach. Please allow me to detail my train of thoughts on the matter and my understanding of where we might agree and disagree. The details might be repetitive from our earlier discussions, but it may help me to synchronize the picture of the problem.

The problem statement (as mailed to you earlier):
------------------------------------------------

"Automate the inter-analyses interaction when information from an analysis A can potentially make analysis B more precise. The soundness of B is not affected by the availability of A."

We might infer here that the meaning of an analysis B should also not change in case of such an automation.


Properties of a model solution:
------------------------------

1. The relative difficulty in the specification of an analysis, within the new framework w.r.t. the current approaches, should be as low as possible.

2. Writer of an analysis shall not be constrained to possess the knowledge of the properties or details of any other analysis. In other words, the writer of an analysis should not be burdened with the task of explicating any external information that could make the analysis more precise.

The point 2 has been a difficult nut to crack. To meet the requirement, one will have to delegate the task of discovery and application of information to a higher entity we have been calling 'The Host'.


Components of 'The Host':
-------------------------

1. Intermediate Representation(IR).

2. Type System.

3. Analysis Specifications.

4. Dependence information. The dependence information is derived using the above three components.

5. Interaction Algorithm.

The "Dependence information" and "Interaction Algorithm" are the holy grail. All that we have been doing boils down to these two components.

Hence we have been investigating to capture the dependence information for quite some time. (The details of the interaction algorithm, although with some understanding, has remained parked as todo.)

The Observation
----------------

In my investigations of analysis dependence w.r.t. "automation", I have only found the following two classes of information useful,

a. Use of the current value of a variable. (Liveness)
b. Property of values of a variable. (set of values, remainder property, and range only)

When I reasoned in terms of "Blocking" Statements, I reached the above conclusion again.


The Confusion
----------------

You have always contended the above observation, and I have always taken that seriously to reinvestigate the observations by hunting for more examples. Your contentions helped me to finally regard the usefulness of liveness information appropriately. The thing that I have continuously failed to find is an example where your hypothesis is useful. Without an example I have always been forced to imagine virtual cases. I beg you, in this regard, to show me a clearer picture where the above observation might fail. An example would be helpful.



------------------------------------------------





------------------------------------------------
Linux Commands <a name="20180712-134751"></a>
================================================
* Keywords: linux commands, useful commands, terminal commands
* Timestamp: 20180712-134751

------------------------------------------------
------------------------------------------------

* send post request to a server (TODO: see using `curl` also)

    wget --post-data "uname=1xx05x0xx&passwd=pg%20xxxx&button=Login" -S https://internet.iitb.ac.in/index.php

* starting python http server in background

    python3 -m http.server >> server.tmp.log 2>&1 &  

------------------------------------------------





------------------------------------------------
ihci paper review <a name="20180718-115400"></a>
================================================
* Keywords: ihci paper review
* Timestamp: 20180718-115400

------------------------------------------------
------------------------------------------------

37: Issues and Challenges in Community Detection Algorithms
------------------------------------------------------------
2/5 : Reject

1. The paper lacks depth. It has only very briefly touched on various issues.

2. Any paper discussing the problems of a field, should invariably discuss and point the reader towards the significant/novel endeavours to overcome most problems posed by authors. In this regard, the paper doesn't complete the objective of a good survey. Moreover, the authors fail to provide valuable insights out of their study. For example, the vairous definitions/views of a community are not rigorously compared with each other. Which one is the best, most used ? What is being done to unify the various views? A tabular comparison and a conclusion after defining all views could have added value.

3. The authors never mention the "maximum clique" problem in the paper, which is a relevant mathematical problem related to the issue.

4. There are minor grammatical and punctuation errors spread across the paper. For example "At last Section 4 concludes the paper," is grammatically wrong. It should be "The last Section 4...," but then one realises it could also be "At last, Section 4..."

5. The conclusion is vague. It has to be crisper than the abstract, so that the reader can take away concrete ideas home. Over and above the abstract, the conclusion doesn't add any value.

6. Images used are of poor quality.



2/5 : Reject

1. Its difficult to find a research component in the paper. What theory is the implementation based on? This appears to be a summer project without the interesting details of a research. There is no quantitative analysis, evaluation, and reasoning about the choices made during development. The important details surrounding this interesting problem are amiss.

2. The paper uses the term "learning" a lot. However, it doesn't define it anywhere.

3. Its an attempt in a good direction. However, it doesn't show how useful it is. Where there any trials conducted? If so, what metric was used to evaluate the ease of use? The paper also lacks a detailed quantitative/qualitative comparison of its ease of use with any other such application. Given the well known nature of the problem, it should not be difficult, on the writer's part, to find other applications catering to similar needs, and doing some interesting comparisons.

4. In the realated work section, how is GPS navigation related to "learning" aspect of the current application??

5. The authors need to reason soundly on why did they choose "vibratory" feedback over other forms.

6. The word "earning" through the app has been used, but never explained.

7. The paper has many grammatical and common English mistakes. For example, "now days" should be "nowadays".


3.5/5: weak accept


38
--------

1. The authors use "increase the efficiency" phrase, when the actuall intent is "increase the accuracy". The keyword "efficiency" misleads the reader into thinking that a space-time advantage is targetted. As far as the results are shown, they don't talk about "efficiency" but only "accuracy". Also the phrase "better than existing..." is used without the nouns "accuracy" or "efficiency". I can infer that "accuracy" is meant here, but should be explicated in writing as well.

2. Fig. 4, and its explanation suggests that one run of each analyzer was used. In learning algorithms, the initial bias may play a significant role in the final outcome. Hence the results should be shown by taking a mean of the perforance of at least 5 randomly biased runs for each method shown.

3. One interesting comparison the authors could (optionally) add, is the comparison with a combined linear model. Since efficiency is not much of a concern here, one can train the given set of 10 different classifiers and run all 10 on the given input file. This process generates a tuple of 10 predicted classes for each file fed. We choose the mode of the tuple as answer. For example, if the input file is abc.mp3, the intermediate output (lets assume) is (Class A, Class B, Class A, Class A, Class C, Class D, Class A, Class B, Class A, Class A), then the final classification would be Class A since it is the most predicted class. A tie can be resolved randomly.

4. Some efficiency metric could have added value to the paper. That is, time and space required to train and test these techniques.

5. The confusion matrix table (Fig. 3) is formatted casually. Its blurry, and in its current form shouldn't make its way to the final publication. Please note, the quality of every table, figure, and image should not distort with magnification. Fig 4 also lacks sharpness. A vector graphics is needed.

6. Another interesting question: Is the observation here also true in general? That is, the authors have shown the current results for musical records only. Does this result match with the comparisons of these methods when applied to other domains. I am sure the authors can find the publications doing a similar exercise in other domains. If not exactly these 10 classifiers, a similar set of classifiers in other domains would help validate the results since there are no formal proofs given.

------------------------------------------------





------------------------------------------------
kernel development <a name="20180719-210720"></a>
================================================
* Keywords: learn kernel development, os development
* Timestamp: 20180719-210720

------------------------------------------------
------------------------------------------------

Thomas Moser, 40+ years OS Development + Consulting
---------------------------------------------------

Read a book or two on the Linux kernel. Robert Love ‘s book is good. Amazon.com: Linux Kernel Development (3rd Edition) (9780672329463): Robert Love: Books

Get a simple, debuggable device like a raspberry pi or other SBC. Or get some old desktop and install a Linux distro on it. Maybe something simple without a gui.

Got that up and running. Great! Be sure you know how to use it well from the command line. Now build and replace the kernel. Just build the same one you installed. Building and installing the kernel is half the battle.

Debug that kernel: Trace some stuff, generate some log messages.

Write a system call to make your caps lock blink 5 times.

Maybe add a new signal or something.

Write a device driver or dick around (*technical kernel developer term) with an existing one.

Write your own disk filesystem.

Try to fix a real kernel bug and get it approved into the real kernel.

By that point you should have your own ideas.


------------------------------------------------





------------------------------------------------
startup applications commands <a name="20180729-223904"></a>
================================================
* Keywords: ubuntu system startup commands, how to
* Timestamp: 20180729-223904

------------------------------------------------
------------------------------------------------

How To
--------------------------
* use `crontab -e` and `@reboot cmd`
* edit `/etc/rc.local`, mark it executable if not. Its read by rc-local.service in systemd, which executes the script automatically on startup. There are ways to add dependencies, such that, the script is executed only when certain services start.



Applications I need at startup
--------------------------

/usr/lib/caribou/caribou

indicator-cpufreq

# Enable mouse click 12
xinput set-prop 12 "libinput Tapping Enabled" 1

# Enable mouse click 13
xinput set-prop 13 "libinput Tapping Enabled" 1

guake

indicator-multiload

# misc important files
/etc/systemd/logind.conf

------------------------------------------------





------------------------------------------------
windows bootable <a name="20180731-123028"></a>
================================================
* Keywords: windows 10 bootable pendrive
* Timestamp: 20180731-123028

------------------------------------------------
------------------------------------------------

Creating a windows 10 bootable disk on linux ubuntu,

    sudo add-apt-repository ppa:nilarimogard/webupd8 
    sudo apt update  
    sudo apt install woeusb

    sudo woeusb --device windows.iso /dev/sdb


------------------------------------------------





------------------------------------------------
installing grub2 on efi with windows 10 <a name="20180801-130323"></a>
================================================
* Keywords: install grub, install grub2 efi, uefi bootloader, windows10
* Timestamp: 20180801-130323

------------------------------------------------
------------------------------------------------

### How to install ubuntu dual load with windows 10?

Summary: Install Windows 10, let it create the EFI partition (by default 100M) and then install Ubuntu. Disable hibernation, secure boot, fast boot of windows. Disable secure boot and fast boot from the bios as well. Then install Ubuntu and if still only windows loads, then boot from the live usb and install grub on the efi partition.

For me the following sequence of commands worked, after booting into the live ubuntu,

    sudo mount /dev/sdXXXX /mnt         # root partition
    sudo mount /dev/sdXXX /mnt/boot     # boot partition
    sudo mount /dev/sdXX /mnt/boot/efi  # efi partition
    for i in /dev /dev/pts /proc /sys /run; do
      sudo mount -B $i /mnt$i;
    done
    sudo chroot /mnt
    sudo apt-get install --reinstall grub-efi-amd64
    grub-install /dev/sdX   # primary disk (/dev/sda mostly)
    update-grub

------------------------------------------------





------------------------------------------------
installing building clang llvm <a name="20180801-201344"></a>
================================================
* Keywords: build clang, build llvm
* Timestamp: 20180801-201344

------------------------------------------------
------------------------------------------------

* Download llvm, clang, clang-tools-extra, lld, from [here](http://releases.llvm.org/download.html) and save them in directory `resources`.


        $ ls ./resources
        llvm-6.0.1.src.tar.xz
        cfe-6.0.1.src.tar.xz                
        clang-tools-extra-6.0.1.src.tar.xz  
        lld-6.0.1.src.tar.xz

* Extract llvm into folder `llvm`. clang into `llvm/tools/clang`. lld into `llvm/tools/lld`. And clang-tools-extra into `llvm/tools/clang/tools/clang-tools-extra`.

* Install `ninja` (`sagi ninja-build`)

* Use `gold` linker (present by default. `sagi binutils`)

* Go to the directory where the `llvm` directory (the root of the source) is located and create a `build` directory (`mkdir build`)

* Use the following cmake command,

        $ mkdir build
        $ cd build
        $ CC=gcc CXX=g++ \
        cmake -G Ninja \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=On \
          -DBUILD_SHARED_LIBS=On \
          -DLLVM_ENABLE_ASSERTIONS=On \
          -DLLVM_TARGETS_TO_BUILD="X86" \
          -DLLVM_ENABLE_SPHINX=Off \
          -DLLVM_ENABLE_THREADS=On \
          -DLLVM_INSTALL_UTILS=On \
          -DCMAKE_BUILD_TYPE=Debug \
          # for libcxx -- del this line
          -DLLVM_ENABLE_LIBCXX=On \
          -DLIBCXX_ENABLE_EXCEPTIONS=On \
          -DLIBCXX_ENABLE_RTTI=On \
          # for libcxx -- del this line
          -DLLVM_USE_LINKER=gold ../llvm

* cmake should run fine. Then invoke `ninja` in the same directory.

------------------------------------------------





------------------------------------------------
span directions <a name="20180803-130252"></a>
================================================
* Keywords: research directions, pros and cons
* Timestamp: 20180803-130252

------------------------------------------------
------------------------------------------------

Direction 1: the eval() way
-----------------------
Pros:
1. A simple approach, where the evaluation of an expression to a `simpler` expression does the trick.
2. Modularity. The client analysis need not be aware of the existence or semantic nature of the server analysis. The blocking statements make things automatic.
3. Modularity. The Host also need not be aware of any analysis. Analyses expose their eval() functions to the Host, which inturn uses them on a case and need basic.
4. Proofs of termination and determinism is a challenge. These proofs would be a novel addition.
5. Combines analyses automatically, without any manual intervention. (novel)
6. Combines forward and backward analyses seamlessly. (novel)
7. Strictly more precise over best known techniques. (novel)

Cons:
1. Too simple.
2. Involves (indirect) transformations of code.

Note: Without evaluation of expressions at one level or another, how else is it possible to interact `beneficially`? (In my opinion, and observations, its not possible)


Direction 2.1: Directly Naming Analyses
----------------------------

This is an orthogonal direction w.r.t. the first one. It adds the convenience of constructing super-analyses, from component analyses.

Pros:
1. Ability to express complex analyses as an ensemble of component (simpler) analyses. Hence, eases the construction of super-analyses.
2. Proofs of soundness and termination for such composition is interesting. (novel)

Cons:
1. All component analyses must be defined beforehand.
2. A rigid system. A client analysis is completely aware of the server analyses.
3. It doesn't solve the "Mutually Beneficial Interaction" problem. Hence, its an orthogonal addition.


Direction 2.2: Specify Semantics
----------------------------

This is an incremental addtion to the direction 2.1. Instead of hard coding the component analyses, one will specify the semantics of information required, and the Host can select the server analysis appropriately.

Pros:
1. Client need only be aware of the semantics of information needed. (vs a hardcoded analysis name) (novel)
2. Invention of a general language for semantic description of information. (novel)
3. Equating similarity of semantics, given two specifications. (Hard) (novel)
4. Proofs of soundness, and termination would be an incremental addition over direction 2.1.

Cons:
1. A complex approach.
2. Strictly requires the client to be aware of the semantics of the information required.
3. Cannot solve the problem of "mutually beneficial interactions" on its own. It still needs evaluation of expressions for such interactions in one form or the other.

------------------------------------------------





------------------------------------------------
essential ubuntu packages <a name="20180803-130643"></a>
================================================
* Keywords: essential ubuntu packages, ubuntu software, ubuntu programs, linux software,
   linux programs.
* Timestamp: 20180803-130643

------------------------------------------------
------------------------------------------------

* `net-tools` : for `netstat` command

* `i3` : i3 window manager
* `arandr` : simple virual front end for XRandR
* `feh` : sets wallpaper
* `network-manager-gnome` : for `nm-applet`
* `system-config-printer-gnome` : printer manager
* `xbacklight` : ajusts screen brighness
* `x11-xserver-utils` : for `xmodmap` (by default)
* `x11-utils` : for program like `xev` (pre installed)

* `links` : text/terminal based internet browser
* `nginx` : http server, reverse proxy
* `vim-gtk3` : vim package with sane features
* `pcmanfm` : replacement for `nautilus`.
* `htop` : better alternative to `top`
* `texlive-full` : complete latex system
* `texmaker` : latex ide (to lookup symbols)
* `graphviz` : for `dot` program
* `xdot` : `xdot` app to render dot language
* `markdown` : markdown language
* `golang-go` : language go compiler
* `swi-prolog` : language prolog interpreter
* `ghc` : the glasgow haskell compilation system
* `ipython3` : interactive python3 interpreter
* `python3-distutils` : useful additions
* `openjdk-8-jdk` : java/javac

* `zsh` : the zsh shell
* `git` : version control system
* `vlc` : videos and audio
* `terminator` : tiling terminal manager
* `curl` : send get/post request
* `apt-file` : search package by filename
* `gthumb` : image viewer and modifier
* `gimp` : gnu image manipulation
* `openssh-server` : for remote ssh
* `tree` : display directory tree
* `ninja-build` : ninja build system
* `cmake` : build config generator
* `ctags` : extracts c/c++ project structure

* `redshift` : to turn off monitor blue light

* `gksu` : graphical sudo user password prompt

* `jpegoptim` : optimize jpeg images
* `pv` : pipe viewer
* `cpu-checker` : for `kvm-ok`, cpu and bios properties checker
* `libnotify-bin` : for `notify-send` command

* https://github.com/zoltanp/xrandr-invert-colors

* moka theme

        sudo add-apt-repository -u ppa:snwh/ppa 
        sudo apt-get install moka-icon-theme faba-icon-theme faba-mono-icons

* adwaita-dark theme (among pre-installed in lubuntu 18.04.1)
  Use `lxappearance` program to switch to this them. Great theme to work at night. New themes have to be extracted to `/usr/share/themes` or `~/.themes`.

* Removing unity and other bloated softwares:

        sudo apt-get autoremove --purge unity unity-common unity-services unity-lens-\* unity-scope-\* unity-webapps-\* gnome-control-center-unity hud libunity-core-6\* libunity-misc4 libunity-webapps\* appmenu-gtk appmenu-gtk3 appmenu-qt\* overlay-scrollbar\* activity-log-manager-control-center firefox-globalmenu thunderbird-globalmenu libufe-xidgetter0 xul-ext-unity xul-ext-webaccounts webaccounts-extension-common xul-ext-websites-integration gnome-control-center gnome-session
------------------------------------------------





------------------------------------------------
managing sound in linux <a name="20180821-191545"></a>
================================================
* Keywords: pulse audio, ubuntu sound
* Timestamp: 20180821-191545

------------------------------------------------
------------------------------------------------

<https://opensource.com/article/17/1/linux-plays-sound>

<https://wiki.archlinux.org/index.php/PulseAudio/Examples#Automatically_switch_audio_to_HDMI>
------------------------------------------------





------------------------------------------------
web application development <a name="20180910-000820"></a>
================================================
* Keywords: python web application, web tools
* Timestamp: 20180910-000820

------------------------------------------------
------------------------------------------------

Some important tools
--------------------
* [bottle.py](https://bottlepy.org) : a minimal python web framework
* [zeromq](http://zeromq.org) : for inter-process communication


------------------------------------------------





------------------------------------------------
qrtools <a name="20180913-102804"></a>
================================================
* Keywords: python qr tools, qr code
* Timestamp: 20180913-102804

------------------------------------------------
------------------------------------------------

Generating and reading QR code in python

* `sudo pip3 install qrtools`
* `sudo apt-get install libzbar-dev`
* `sudo pip3 install zbar` -- zbar is not supported on py..3, its active development stopped in 2009 :(

TODO: first attempt failed as support for python3 is amiss.


------------------------------------------------





------------------------------------------------
haskell stack error <a name="20180927-160647"></a>
================================================
* Keywords: haskell stack error
* Timestamp: 20180927-160647

------------------------------------------------
------------------------------------------------

First method of installing and using `stack` failed,

    $ stack install hindent stylish-haskell
    Writing implicit global project config file to: /home/codeman/.stack/global-project/stack.yaml
    Note: You can change the snapshot via the resolver field there.
    Using latest snapshot resolver: lts-12.10
    Downloaded lts-12.10 build plan.    
    AesonException "Error in $.packages.cassava.constraints.flags['bytestring--lt-0_10_4']: Invalid flag name: \"bytestring--lt-0_10_4\""
    
    stack install hindent stylish-haskell
    Downloaded lts-12.10 build plan.    
    AesonException "Error in $.packages.cassava.constraints.flags['bytestring--lt-0_10_4']: Invalid flag name: \"bytestring--lt-0_10_4\""


Second method looks promising,

    $ curl -sSL https://get.haskellstack.org/ | sh
    Detected Linux distribution: ubuntu
    
    Installing dependencies...
    
    Reading package lists... Done
    Building dependency tree       
    Reading state information... Done
    g++ is already the newest version (4:7.3.0-3ubuntu2).
    g++ set to manually installed.
    gcc is already the newest version (4:7.3.0-3ubuntu2).
    gcc set to manually installed.
    libc6-dev is already the newest version (2.27-3ubuntu1).
    libffi-dev is already the newest version (3.2.1-8).
    libffi-dev set to manually installed.
    libgmp-dev is already the newest version (2:6.1.2+dfsg-2).
    libgmp-dev set to manually installed.
    make is already the newest version (4.1-9.1ubuntu1).
    make set to manually installed.
    xz-utils is already the newest version (5.2.2-1.3).
    zlib1g-dev is already the newest version (1:1.2.11.dfsg-0ubuntu2).
    git is already the newest version (1:2.17.1-1ubuntu0.1).
    gnupg is already the newest version (2.2.4-1ubuntu1.1).
    0 upgraded, 0 newly installed, 0 to remove and 154 not upgraded.
    
    Using generic bindist...
    
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
    100   621    0   621    0     0    661      0 --:--:-- --:--:-- --:--:--   660
    100 13.3M  100 13.3M    0     0   312k      0  0:00:43  0:00:43 --:--:--  329k
    Installing Stack to: /usr/local/bin/stack...


    -------------------------------------------------------------------------------
    
    Stack has been installed to: /usr/local/bin/stack

------------------------------------------------





------------------------------------------------
habits to cultivate/cultivated to keep <a name="20181010-195342"></a>
================================================
* Keywords: cultivation of habits 
* Timestamp: 20181010-195342

------------------------------------------------
------------------------------------------------

Food
-----
* prefer brown rice
* 95% vegetarian diet
* drink glucose twice a day

Exercise
----------
* daily exercise (with 3 days heavy exercise per week)
* run twice a week (take it above 2km in one go)
* repeat set of 5 deep breaths, at least five times a day

Learning
----------
* daily language learning exercise
* read one book every week

Sleep routine
--------------
* 8 hour night sleep  (11pm to 7am)
* brush before sleep
* drink water eat fruits just after bed
* take short naps between work breaks (huge enhancer)

Work ethics
-----------
* adhere strictly to time - end and start things on time
* focus on getting things done -- postpone secondary tasks
* one, at most two tasks at a given time
* sit straight
* separate work place from casual routines
* hone what you have
 
Food
-----
* prefer brown rice
* 95% vegetarian diet
* drink glucose twice a day
* drink >2L water daily
* prefer low fat diet

Bad habits
-----------
* no nose digging
* no nail biting
* no hair touching
* w\_\_k at most twice a week
* videos only on weekends


------------------------------------------------





------------------------------------------------
research direction <a name="20181020-165925"></a>
================================================
* Keywords: research direction
* Timestamp: 20181020-165925

------------------------------------------------
------------------------------------------------

Possible sequence of work,

1. Compile time interpretation. (implementation + paper)
   * Upgrading implementation to haskell.
2. Linking with specification of data flow information needed.
3. Survey of analyses interaction.



------------------------------------------------





------------------------------------------------
math and string library <a name="20181106-104420"></a>
================================================
* Keywords: math string library compilation
* Timestamp: 20181106-104420

------------------------------------------------
------------------------------------------------

Some alternative math libraries,
* <openlibm.org> - is it portable to sparc-\* ?
* <http://www.netlib.org/fdlibm/> - only double precision supported

------------------------------------------------





------------------------------------------------
quora answer <a name="20181110-185112"></a>
================================================
* Keywords: komal paper cc
* Timestamp: 20181110-185112

------------------------------------------------
------------------------------------------------
Despite having tons of engineers, why does India lag behind China in making renowned mobile hardware and software?

Short answer: Lack of vision and skill.

There are many tangible reasons for the "poor" Indian engineering state. But instead of only highlighting and fire figthing the situation, lets focus on the cause.

Lack of vision (and hence initiative)
----------------

Vision is THE factor for initiative taking individuals. One has to see first, to materialize a goal. Lets understand it with some well observed scenarios.

Scenario 1: ISRO launches its successful PSLV rocket. Critics come rushing in, opposing the scientific investment and force the government to direct money towards immediate problems of the nation. The "weak" government redirects the funds, and the scientific community of the nation becomes disappointed. Now, who wants to be a part of ISRO which is not celebrated enough in the country vs an opportunity at NASA? 

This scenario, although more perfectly suitable for a decade ago, has done a considerable damage by pushing bright minds away from Indian institutes of excellence and into the hands of foreign beneficiaries. The current stupendous achievements of ISRO come from just 10-20% of its workforce, which remained focused on the vision, despite the nation downplaying their efforts for so long. And now the situation has just started to improve when the foreign media and leaders have started recognizing and praising ISRO's efforts. I am sure, this change of veiw point towards ISRO of the general public, will show its tangible results in the coming decade. The problem is, Indians want a "foreign" stamp for what is "good" and what is "bad." (A convincing proof of this can be seen on YouTube, where "foreigner's reaction" on XYZ Indian videos garners millions of views, vs some purely Indian content with much candid content alongside in suggestions.)

When India as a whole largely appreciates the vision that few maverik take upon their shoulders to fulfill without the burden of proving again and again the merit of such endeavour, then India will immedeately see fruits of such shift. I can observe positive signs of change in this regard.

Scenario 2: A pure Indian startup becomes popular, and/or profitable with revenue pouring in. Foreign investors pour in and offer to buy the business for a "huge" sum of money. The owner(s) decide to sell and make themselves "easy" money, without realising that they lost orders of magnitude of money that the business would have generated for them in the coming years. Such examples are many, from Thumbs Up to Flipkart.

What difference does it make? 
 


* Only 7 per cent engineering graduates employable: What's wrong with India's engineers?
  <https://www.indiatoday.in/education-today/featurephilia/story/engineering-employment-problems-329022-2016-07-13>

------------------------------------------------






------------------------------------------------
compiling glibc <a name="20181115-151036"></a>
================================================
* Keywords: glibc
* Timestamp: 20181115-151036

------------------------------------------------
------------------------------------------------

1. (glibc-math/glibc/glibc-2.28/INSTALL file)
...the most recent kernel you can get your hands on.  (If you are
cross-compiling the GNU C Library, you need to specify
'ARCH=ARCHITECTURE' in the 'make headers_install' command, where
ARCHITECTURE is the architecture name used by the Linux kernel, such as
'x86' or 'powerpc'.)

2. (glibc-math/glibc/glibc-2.28/INSTALL file)
   It may also be useful to pass 'CC=COMPILER' and 'CFLAGS=FLAGS'
arguments to 'configure'.  'CC' selects the C compiler that will be
used, and 'CFLAGS' sets optimization options for the compiler.  Any
compiler options required for all compilations, such as options
selecting an ABI or a processor for which to generate code, should be
included in 'CC'.  Options that may be overridden by the GNU C Library
build system for particular files, such as for optimization and
debugging, should go in 'CFLAGS'.  The default value of 'CFLAGS' is '-g
-O2', and the GNU C Library cannot be compiled without optimization, so
if 'CFLAGS' is specified it must enable optimization.  For example:

     $ ../glibc-VERSION/configure CC="gcc -m32" CFLAGS="-O3"


    $ INSTALL_DIRECTORY="/home/codeman/include"
    glibc-src-dir $ make headers_install INSTALL_HDR_PATH=INSTALL_DIRECTORY ARCH=ARCHITECTURE
    glibc-build-dir $ ../glibc-VERSION/configure CC="sparc-linux-gcc" --with-headers=INSTALL_DIRECTORY/include

    /usr/local/ajit_release/tools/ajit_access_routines/asm/trap_handlers.s

    sparc-linux-gcc  -c  -S -Wall -Werror -m32 -mcpu=v8 -nostdlib -ffreestanding   -O3  -ffreestanding -fschedule-insns -fschedule-insns2 -frename-registers     -I /usr/local/ajit_release/tools/ajit_access_routines/include  -I include/  -I env/  -I /usr/include  -D ITERATIONS=2000  -D CORE_DEBUG=0  -D COMPILER_REQUIRES_SORT_RETURN=1  env//cvt.c -o .//sparc-assembly/cvt.s

    sparc-linux-as   -Av8 .//sparc-assembly/core_state.s  -o .//sparc-obj/core_state.o

    sparc-linux-ld  -e main -T LinkerScript.lnk .//sparc-obj/init.o  .//sparc-obj/trap_handlers.o  .//sparc-obj/core_state.o  .//sparc-obj/cvt.o  .//sparc-obj/ee_printf.o  .//sparc-obj/core_list_join.o  .//sparc-obj/core_portme.o  .//sparc-obj/ajit_access_routines.o  .//sparc-obj/core_matrix.o  .//sparc-obj/core_main.o  .//sparc-obj/core_util.o   -o .//core_mark.elf

CC="sparc-linux-gcc"

CFLAGS="

------------------------------------------------





------------------------------------------------
setup new system <a name="20181124-104741"></a>
================================================
* Keywords: new system setup
* Timestamp: 20181124-104741

------------------------------------------------
------------------------------------------------

* assuming username is `codeman`
* create basic directory structure

        mkdir -p /home/codeman/.itsoflife/{git,local,remote}

* set the environment variable in `/etc/environment`

        echo "MYDATA=/home/codeman/.itsoflife" | sudo tee -a /etc/environment
        # IMPORTANT: logout and login for the variable to take effect!

* install basic programs

        sudo apt-get update
        sudo apt-get install -y git
        sudo apt-get install -y vim-gtk3
        sudo apt-get install -y zsh
        # optional
        sudo apt-get install -y tree

* clone basic git repos.

        cd $MYDATA/git
        git clone https://github.com/adhuliya/bin.git
        git clone https://github.com/adhuliya/configs.git
        mv bin bin-git
        mv configs configs-git

* install vundle

        git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

* install ohmyzsh

        sh -c "$(wget https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"

* copy configuration files

        rm -Rf .vimrc .vim .zshrc
        cp -r $MYDATA/git/configs-git/sys-files/nintel05/home/codeman/{.vimrc,.vim,.zshrc} ~/ 

* open vim and issue command `:PluginInstall`

------------------------------------------------





------------------------------------------------
linux from scratch <a name="20181124-130242"></a>
================================================
* Keywords: linux from scratch notes, lfs notes
* Timestamp: 20181124-130242

------------------------------------------------
------------------------------------------------

Programs and packages needed:
------------------------------
1. Bash-3.2 (/bin/sh should be a symbolic or hard link to bash)
   `sagi bash`

2. Binutils-2.25 (Versions greater than 2.31.1 are not recommended as they have not been tested)
   `sagi binutils binutils-dev binutils-source`

3. Bison-2.7 (/usr/bin/yacc should be a link to bison or small script that executes bison)
   `sagi bison libbison-dev`

4. Bzip2-1.0.4
   `sagi bzip2 libzip-dev`

5. Coreutils-6.9
   `sagi coreutils policycoreutils-dev`

6. Diffutils-2.8.1
   `sagi diffutils`

7. Findutils-4.2.31
   `sagi findutils`

8. Gawk-4.0.1 (/usr/bin/awk should be a link to gawk)
   `sagi gawk`

9. GCC-4.9 including the C++ compiler, g++ (Versions greater than 8.2.0 are not recommended as they have not been tested)
   `sagi gcc g++`

10. Glibc-2.11 (Versions greater than 2.28 are not recommended as they have not been tested)
    AD: comes along with gcc/g++

11. Grep-2.5.1a
    `sagi grep`

12. Gzip-1.3.12
    `sagi gzip`

13. Linux Kernel-3.2
    AD: (more recent version) Comes with lubuntu 18.04.1

    The reason for the kernel version requirement is that we specify that version when building glibc in Chapter 6 at the recommendation of the developers. It is also required by udev.

    If the host kernel is earlier than 3.2 you will need to replace the kernel with a more up to date version. There are two ways you can go about this. First, see if your Linux vendor provides a 3.2 or later kernel package. If so, you may wish to install it. If your vendor doesn't offer an acceptable kernel package, or you would prefer not to install it, you can compile a kernel yourself. Instructions for compiling the kernel and configuring the boot loader (assuming the host uses GRUB) are located in Chapter 8.

14. M4-1.4.10
    `sagi m4`

15. Make-4.0
    `sagi make`

16. Patch-2.5.4
    `sagi patch patchutils`

17. Perl-5.8.8
    `sagi perl`

18. Sed-4.1.5
    `sagi sed`

19. Tar-1.22
    `sagi tar`

20. Texinfo-4.7
    `sagi texinfo`

21. Xz-5.0.0
    `sagi xz-utils`

------------------------------------------------





------------------------------------------------
qemu <a name="20190111-112349"></a>
================================================
* Keywords: qemu debian setup
* Timestamp: 20190111-112349

------------------------------------------------
------------------------------------------------

### Command sequence:

    sudo apt-get install qemu-system-sparc
    sudo apt-get install openbios-sparc
    cd /home/codeman/.itsoflife/local/packages-live/qemu-data
    wget https://cdimage.debian.org/mirror/cdimage/archive/4.0_r3/sparc/iso-cd/debian-40r3-sparc-netinst.iso
    qemu-img create -f qcow hda.img 10G
    // install/setup the system : use defaults.
    qemu-system-sparc -hda hda.img -cdrom debian-40r3-sparc-netinst.iso -boot d
    // launch the new system
    qemu-system-sparc -hda sparc.img

`qemu-system-sparc` simulates sparcV8, [microSPARC][] II (Swift), model Fujitsu MB86904 processor. This is the [sun4m][] machine.

Notes
------
* The system has no binutils and gcc installed. Just `gcc-4.1-base` and general bash utilities.
* Network/Internet works out of the box.
* Don't know how to get gcc compiler setup, no binary build for the machine found!

Resource
----------
* [debian sparc qemu][]
* [microSparc][]
* [sun4m][]

[debian sparc qemu]: https://www.aurel32.net/info/debian_sparc_qemu.php
[microsparc]: https://en.wikipedia.org/wiki/MicroSPARC
[sun4m]: https://wiki.qemu.org/Documentation/Platforms/SPARC

------------------------------------------------





------------------------------------------------
prof kartik  <a name="20190117-154838"></a>
================================================
* Keywords: prof kartik
* Timestamp: 20190117-154838

------------------------------------------------
------------------------------------------------

rhaodinia stamp benchmarks
svcomp -- software verification computation.

------------------------------------------------





------------------------------------------------
Convert VOB to mp4 <a name="20190323-152759"></a>
================================================
* Keywords: convert, vob to mp4 ...
* Timestamp: 20190323-152759

------------------------------------------------
------------------------------------------------

Please see what is in these files

Place all VOBs in a folder then >>

Code:

 sudo apt install mediainfo

Code:

 mediainfo   *VOB*

so to convert keeping highest possible values shown by mediainfo
to use for a "bulk convert" [change the values you found for audio and video and lower if you want smaller size]


Code:

for f in *.VOB ; do ffmpeg -i "$f" -b:v 3000k  -b:a 128k "${f%.*.VOB}.mp4"; done


------------------------------------------------





------------------------------------------------
Prof. Ashish Pandey <a name="20190331-224713"></a>
================================================
* Keywords: 
* Timestamp: 20190331-224713

------------------------------------------------
------------------------------------------------

+ve psychology
mindfullness

yoga
spirituality in management
indian psychology

Prof. Bhawuk (Univ. of Huawai)
read papers in music (bhakti yoga, mantras)
chirag dagar

------------------------------------------------





------------------------------------------------
SERI IISC Bangalore <a name="20190506-104010"></a>
================================================
* Keywords: ACM Software Engineering Research in India (SERI)
* Timestamp: 20190506-104010

------------------------------------------------
------------------------------------------------
July 12-13th.

Edit response link:

https://docs.google.com/forms/d/e/1FAIpQLSeuwpW_YPuSLCWEzE5Bi607MmQhwB4LfMtf6sNHOamdwZ7Tlg/viewform?embedded=true&usp=form_confirm&edit2=2_ABaOnuec5OnoWi1w6__1kb3mgojdr6Epmb6Wjm9r2h4F4NFSz_HhRK_xMnScrWZEUOHSGu0

------------------------------------------------





------------------------------------------------
AJIT Debuggin <a name="20190506-170732"></a>
================================================
* Keywords: ajit debugging, gdb
* Timestamp: 20190506-170732

------------------------------------------------
------------------------------------------------

    ajit_C_system_model -m test_pow.mmap.remapped -w test_pow.wtrace -g -p 999


------------------------------------------------





------------------------------------------------
sanjose issue <a name="20190506-234626"></a>
================================================
* Keywords: snajose issue, gdb
* Timestamp: 20190506-234626

------------------------------------------------
------------------------------------------------

    sanjose@AJIT2:~/code_test/new_instn/slld_srld-anshuman$ sparc-linux-gdb --args slld_srld.elf
    Python Exception <type 'exceptions.ImportError'> No module named gdb: 
    
    warning: 
    Could not load the Python gdb module from `/home/nehak/AJITproject/AjitRepoV2/tools/buildroot/buildroot-2014.08/output/host/usr/share/gdb/python'.
    Limited Python support is available from the _gdb module.
    Suggest passing --data-directory=/path/to/gdb/data-directory.
    
    GNU gdb (GDB) 7.6.2
    Copyright (C) 2013 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "--host=x86_64-unknown-linux-gnu --target=sparc-buildroot-linux-uclibc".
    For bug reporting instructions, please see:
    <http://www.gnu.org/software/gdb/bugs/>...
    Reading symbols from /home/sanjose/code_test/new_instn/slld_srld-anshuman/slld_srld.elf...(no debugging symbols found)...done.
    (gdb) target remote :9998
    Remote debugging using :9998
    0x00000000 in start ()
    (gdb) break *0x4
    Breakpoint 1 at 0x4
    (gdb) continue
    Continuing.
    
    Breakpoint 1, 0x00000004 in start ()
    (gdb) display/i $pc
    1: x/i $pc
    => 0x4 <start+4>:	clr  %g3
    (gdb) info registers g2 g3 g6 g7
    g2             0x1	1
    g3             0x94211f2	155324914
    g6             0x4c04a8af	1275373743
    g7             0x1716703b	387346491
    (gdb) si
    0x00000008 in start ()
    1: x/i $pc
    => 0x8 <start+8>:	mov  1, %g6
    (gdb) info registers g2 g3 g6 g7
    g2             0x1	1
    g3             0x0	0
    g6             0x4c04a8af	1275373743
    g7             0x1716703b	387346491
    (gdb) si
    0x0000000c in start ()
    1: x/i $pc
    => 0xc <start+12>:	clr  %g7
    (gdb) info registers g2 g3 g6 g7
    g2             0x1	1
    g3             0x0	0
    g6             0x1	1
    g7             0x1716703b	387346491
    (gdb) si
    0x00000010 in start ()
    1: x/i $pc
    => 0x10 <start+16>:	unknown
    (gdb) info registers g2 g3 g6 g7
    g2             0x1	1
    g3             0x0	0
    g6             0x1	1
    g7             0x0	0
    (gdb) si
    0x00000014 in start ()
    1: x/i $pc
    => 0x14 <start+20>:	ta  0
    (gdb) info registers g2 g3 g6 g7
    g2             0x1	1
    g3             0x0	0
    g6             0x8000000	134217728
    g7             0x0	0
    (gdb) 


------------------------------------------------





------------------------------------------------
SERI Abstarct <a name="20190527-104137"></a>
================================================
* Keywords: seri 2019 abstract
* Timestamp: 20190527-104137

------------------------------------------------
------------------------------------------------

Many analyses are known to mutually benefit from each other. The classical work on conditional constant propagation was one of the first attemts to exploit this property, followed by many other that combined pointer analysis with various other analyses.  The most common way to exploit this interaction has been to manually design a super analysis over a combined lattice, formed by taking the cross-product of domains of each participating analysis.

Synergistic Program ANalyzer (SPAN) is a framework that generates analyses from their specification and automates their mutually beneficial interactions by using a notion called *blocking expressions*. It has mechanisms to automatically select analyses, combine forward/backward flow problems, and provide more precise results than available through other similar contemporary frameworks.

------------------------------------------------





------------------------------------------------
old linked-in "About" <a name="20191001-114329"></a>
================================================
* Keywords: linkedin about
* Timestamp: 20191001-114329

------------------------------------------------
------------------------------------------------
I like programming. I have worked on C, C++, .NET and Java. I have experience in J2EE bank loan application maintenance. Currently I train others on Java Technology, and use it for most of the programming tasks. I wish to add PHP in my arsenal. 

My research interest is in Cognitive Learning Architectures that one day will challenge human intelligence straight on. I believe these architectures are possible and can surpass human intelligence one day. I am working on a self developed semantic network called Receptive Interconnections through Micro-fuzzy Interactions Network (RIMINET). This network has been used in creating a novel classifier based on the concept of analogy and contextual knowledge. I, under the guidance of Prof. U.S. Tiwary (one of the renowned professors in India and abroad), am planning to expand this network into a complete intelligent system.

Specialties: Certified Java Programmer and experience in Java as a J2EE application modification and bug fixing.


------------------------------------------------





------------------------------------------------
Network Settings Ubuntu <a name="20191227-001819"></a>
================================================
* Keywords: command line network settings in ubuntu
* Timestamp: 20191227-001819

------------------------------------------------
------------------------------------------------

* See the IP address and names of all the interfaces:

        ip addr        # method 1
        ifconfig       # method 2

* See all the network interfaces:

        ip link show   # method 1
        ifconfig -a    # method 2 - `-a` displays interfaces even if its down

* For dynamic configuration of interface `wlp3s0`,
  add the following lines to `/etc/network/interfaces`:

        #Configuration for interface wlp3s0
        auto wlp3s0
        iface wlp3s0 inet dhcp

* For static configuration of interface `wlp3s0`,
  add the following lines to `/etc/network/interfaces`:

        #Configuration for interface wlp3s0
        auto wlp3s0
        iface wlp3s0 inet static
        address 192.168.1.151
        netmask 255.255.255.0
        gateway 192.168.1.1
        dns-nameservers 10.200.1.11

  In some systems `dns-nameserver` works (each nameserver in its own line) 
  instead of `dns-nameservers` (which accomodates all space-separated nameservers in 
  a single line) (Not experienced this yet).

* To bring the settings of `/etc/network/interfaces` into
  effect do:

        sudo systemctl restart NetworkManager

* see `man interfaces` on info on `/etc/network/interfaces`
* Read from this source: <https://www.tecmint.com/linux-networking-commands/>
* See Chapter 4 in : <https://help.ubuntu.com/lts/serverguide/serverguide.pdf>
* Check if this i useful: <http://www.haifux.org/lectures/172/netLec.pdf>

------------------------------------------------





------------------------------------------------
Autostart <a name="20191230-142531"></a>
================================================
* Keywords: autostart in ubuntu
* Timestamp: 20191230-142531

------------------------------------------------
------------------------------------------------

Reference:
1. <https://wiki.lxde.org/en/Autostart>
2. <https://wiki.lxde.org/en/LXSession#Autostarted_applications_using_lxsession>

------------------------------------------------





------------------------------------------------
LXDE Wiki <a name="20191230-150520"></a>
================================================
* Keywords: lxde wiki, lxde desktop environment
* Timestamp: 20191230-150520

------------------------------------------------
------------------------------------------------
1. <https://wiki.lxde.org/en/Main_Page>
2. <https://wiki.lxde.org/en/LXDE:Questions> -- seems very useful


------------------------------------------------





------------------------------------------------
easy piano songs <a name="20191231-211546"></a>
================================================
* Keywords: easy piano songs, simple piano songs
* Timestamp: 20191231-211546

------------------------------------------------
------------------------------------------------

Resource:
* <https://www.youtube.com/watch?v=3awdYvj-nhc>


------------------------------------------------


