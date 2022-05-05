%define _topdir /root/topmdt

%define name topmdt
%define release 0%{?dist}
%define version 1.1
%define buildroot %{_topdir}/BUILD/

BuildRoot: %{buildroot}
Summary: topmdt
Name: %{name}
Version: %{version}
Release: %{release}
Group: System
License: GPL
Packager: quentin.bouyer@gmail.com
Requires: glib2

%description
topmdt show open/get_attribute done by client on all mdt

%build
cd %{_sourcedir};
make

%install
rm -fR $RPM_BUILD_ROOT;
mkdir -p $RPM_BUILD_ROOT/usr/bin;
mkdir -p $RPM_BUILD_ROOT/etc;
mkdir -p $RPM_BUILD_ROOT/usr/share/man/man1;
cd %{_sourcedir};
cp topmdt $RPM_BUILD_ROOT/usr/bin;
cp topmdt.conf $RPM_BUILD_ROOT/etc;
cp topmdt.1 $RPM_BUILD_ROOT/usr/share/man/man1;
cp topmdt.conf.1 $RPM_BUILD_ROOT/usr/share/man/man1;
%clean
rm -rf RPM_BUILD_ROOT/
%files
%attr(755,root,root)
/usr/bin/topmdt
/usr/share/man/man1/topmdt.1.gz
/usr/share/man/man1/topmdt.conf.1.gz
/etc/topmdt.conf
%dir
