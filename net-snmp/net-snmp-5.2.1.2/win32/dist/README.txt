       README file for win32 binary release of Net-SNMP

DISCLAIMER

  The Authors assume no responsibility for damage or loss of system
  performance as a direct or indirect result of the use of this
  software.  This software is provided "as is" without express or
  implied warranty.


TABLE OF CONTENTS

  Disclaimer
  Table Of Contents
  Introduction
* Installation
* Co-existence with Microsoft SNMP services
  Installation - Perl module
* Configuration
  Build Information

  * = Required Reading.


INTRODUCTION

  This package contains a compiled binary release of Net-SNMP for Windows NT/2000/XP.
  The binaries run unmodified on Windows 98.  The "snmpd" and "snmptrapd" program can 
  not run as services on Windows 98, as Windows 98 does not provide a Service Control 
  Manager (SCM).

  Documentation for using the applications is available in the Windows help file
  (Net-SNMP.chm) located in the docs directory of the installed package.  Help is also
  available from the web site at http://www.net-snmp.org/docs/.


INSTALLATION

  The Net-SNMP Windows installer package performs the following tasks:

  - Installs the Net-SNMP binaries, MIB files and ActiveState 5.8.x Perl PPM 
    package into the installation folder (defaults to c:\usr). 
  - Adds (install folder)\bin to the system PATH. 
  - Adds the following registry keys:
    - HKEY_LOCAL_MACHINE\Software\Net-SNMP\SNMPCONFPATH=(install folder)/etc/snmp
    - HKEY_LOCAL_MACHINE\Software\Net-SNMP\SNMPSHAREPATH=(install folder)/share/snmp
  - Creates an snmp.conf file in SNMPCONFPATH which defines: 
    - mibdirs (install folder)/share/snmp/mibs 
    - persistentDir (install folder)/snmp/persist 
    - tempFilePattern (install folder)/temp/snmpdXXXXXX 

  After installing using the setup wizard, perform a quick test to verify that 
  Net-SNMP was installed correctly.  Run the following from a command prompt:

    snmptranslate -IR -Td IF-MIB::linkDown

  The above command should generate:

    IF-MIB::linkDown
    linkDown NOTIFICATION-TYPE
      -- FROM       IF-MIB
      OBJECTS       { ifIndex, ifAdminStatus, ifOperStatus }
      DESCRIPTION   "A linkDown trap signifies that the SNMP entity, acting in
                an agent role, has detected that the ifOperStatus object for
                one of its communication links is about to enter the down
                state from some other state (but not from the notPresent
                state).  This other state is indicated by the included value
                of ifOperStatus."
    ::= { iso(1) org(3) dod(6) internet(1) snmpV2(6) snmpModules(3) snmpMIB(1) 
          snmpMIBObjects(1) snmpTraps(5) 3 }

  If snmptranslate can not be found, then verify that the Net-SNMP bin folder is in 
  your system path.

  If you get Module not found errors such as 'IP-MIB: Module not found', the application
  was not able to locate the mibs folder.  Verify that SNMPCONFPATH is set to the location
  of the conf folder (c:/usr/etc/snmp for example).  Also verify that there is a snmp.conf
  file in that folder that contains configuration values for mibdirs, persistentDir and
  tempFilePattern.  For example:

    mibdirs c:/usr/share/snmp/mibs
    persistentDir c:/usr/snmp/persist
    tempFilePattern C:/usr/temp/snmpdXXXXXX

  For detailed information on using environment variables and the registry to configure
  Net-SNMP, see 'Overview' document in the Configuration section of the Net-SNMP help file.

  For information on running snmpd.exe and snmptrapd.exe as a Windows service, see 
  'How to Register the Net-SNMP Agent and Trap Daemon as Windows services' in README.win32.

CO-EXISTENCE WITH MICROSOFT SNMP SERVICES

If the Microsoft SNMP agent service (SNMP Service) is running, the Net-SNMP agent (snmpd) 
will fail to start as it will not be able to bind to the default TCP/IP port of 161.

If the Microsoft SNMP Trap Receiver service is running, the Net-SNMP trap receiver (snmptrapd) 
will fail to start as it will not be able to bind to the default TCP/IP port of 162.

For most users, it is recommended that either the Microsoft or Net-SNMP version of the 
application be used, not both.

To allow both the Microsoft and Net-SNMP agent / trap receiver to run at the same time, the
default TCP/IP port must be changed on either the Microsoft or Net-SNMP version of the 
application.

The Microsoft services use the 'snmp' and 'snmptrap' entries in the SERVICES file 
(%SystemRoot%\SYSTEM32\DRIVERS\ETC\SERVICES) to determine the port to bind the service to 
when the service starts.  Simply modify the entries and restart the affected services.

The Net-SNMP ports for snmpd and snmptrapd can be modified via snmpd.conf and snmptrapd.conf 
or by using a command line option with each program.  See the Net-SNMP Help file for 
instructions on changing the port number.

Note:  Changing the default port the service listens on will prevent it from accepting
       requests or receiving traps from standard SNMP devices and management stations 
       unless they have also been reconfigured to use the new port numbers.

Some users have reported success in configuring the Net-SNMP snmpd agent service to 'proxy' 
requests for Microsoft objects which are not available in the Net-SNMP agent.  This is done 
by changing the default Microsoft 'SNMP Service' port and configuring a PROXY value in snmpd 
to connect to 'localhost:newportnumber' for the 'HOST' value.


INSTALLATION - PERL MODULE

  Included in the (install folder)\Perl folder is an ActiveState Perl 
  5.8.x. PPM package.

  The Perl modules require the Win32 REGEX (Regular Expression) package which 
  is available from:

    http://people.delphiforums.com/gjc/gnu_regex.html

  Download gnu_regex.exe, copy it to a temporary file and execute it to 
  extract the files.

  Copy the extracted gnu_regex.dll to your %windir%\system32 folder.

  Remove any existing Net-SNMP Perl modules:

    ppm remove Net-SNMP

  Install the Perl modules:

    cd (install folder)\Perl
    ppm install Net-SNMP.ppd

  Perform a basic test using:

    net-snmp-perl-test.pl


CONFIGURATION

  All configuration files should be placed in the %SNMPCONFPATH% folder.

  Note: All paths in configuration files should use forward slashes (Unix style), 
  NOT back slashes.  Example: c:/usr

  Included is a Perl script called snmpconf which can be used to create 
  configuration files.  

  Documentation for using the snmpconf is available in the Windows help file
  (Net-SNMP.chm) located in the docs directory of the installed package.  Help is also
  available from the web site at http://www.net-snmp.org/docs/.

  To run snmpconf, use the following command line:

     snmpconf -i


BUILD INFORMATION

  Name:			net-snmp-x.x.x-1.win32.exe
  URL:			http://www.net-snmp.org
  Build date:		
  Built by:		
  Installer Package by: 
  
  OS:			Windows 2000 SP3
  Compiler:		MSVC++ 6.0 SP5
  Platform SDK:		February 2003
  Perl:			ActivePerl 5.8.2 build 808
  REGEX:		gnu_regex.exe (0.12) - http://people.delphiforums.com/gjc/gnu_regex.html

  Source: 		net-snmp-x.x.x.tar.gz
  Destination:  	c:\usr
  Project:		win32sdk.dsw / libdll.dsw
  Library:		netsnmp for applications, netsnmp.dll for Perl modules
  OpenSSL:		n/a


  The following are the default paths are used by the applications:

  ----------------------------------------------------------------------------
  net-snmp-config.h define   | value                    | environment variable
  ----------------------------------------------------------------------------
  DEFAULT_MIBDIRS:           | c:/usr/share/snmp/mibs   | MIBDIRS
  SNMPDLMODPATH:             | c:/usr/lib/dlmod         | SNMPDLMODPATH
  SNMPLIBPATH:               | c:/usr/lib               | SNMPLIBPATH
  SNMPSHAREPATH:             | c:/usr/share/snmp        | SNMPSHAREPATH
  SNMPCONFPATH:              | c:/usr/etc/snmp          | SNMPCONFPATH
  PERSISTENT_DIRECTORY:      | c:/usr/snmp/persist      | SNMP_PERSISTENT_FILE
  NETSNMP_TEMP_FILE_PATTERN: | c:/usr/temp/snmpdXXXXXX  | 

