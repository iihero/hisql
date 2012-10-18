# Configuration arguments for vcbuild.
use strict;
use warnings;

our $config = {
    asserts=>1,			# --enable-cassert
    # integer_datetimes=>1,   # --enable-integer-datetimes - on is now default
    # float4byval=>1,         # --disable-float4-byval, on by default
    # float8byval=>0,         # --disable-float8-byval, off by default
    # blocksize => 8,         # --with-blocksize, 8kB by default
    # wal_blocksize => 8,     # --with-wal-blocksize, 8kb by default
    # wal_segsize => 16,      # --with-wal-segsize, 16MB by default
    nls=>undef,				# --enable-nls=<path>
    tcl=>undef, #'c:\tcl',		# --with-tls=<path>
    perl=>'c:\perl', 			# --with-perl
    python=>'D:\tools\python25', # --with-python=<path>
    krb5=>'E:\learn\db_research\postgreSQL\coding\depend\kfw-3-2-2-final', # --with-krb5=<path>
    ldap=>1,			# --with-ldap
    openssl=>'E:\learn\db_research\postgreSQL\coding\depend\openssl', # --with-ssl=<path>
    uuid=>'E:\learn\db_research\postgreSQL\coding\depend\ossp-uuid', #--with-ossp-uuid
    xml=>'E:\learn\db_research\postgreSQL\coding\depend\libxml',
    xslt=>'E:\learn\db_research\postgreSQL\coding\depend\libxslt',
    iconv=>'E:\learn\db_research\postgreSQL\coding\depend\iconv',
    zlib=>'E:\learn\db_research\postgreSQL\coding\depend\zlib'# --with-zlib=<path>    
};

1;
