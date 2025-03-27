#!/usr/bin/env perl

use strict;
use warnings;
use Cwd qw[getcwd abs_path];
use File::Spec;

sub sys {
    my @args = @_;
    print STDERR join(' ', @args) . "\n";
    my $rc = system(@args);
    if($rc != 0) {
        print STDERR "Command " . join(' ', @args) . " failed with $rc\n";
        exit($rc >> 8);
    }
    return 1;
}

sub getdir {
    my $self_path = shift @_;

    my ($volume, $directory, $file) = File::Spec->splitpath($self_path);
    return $volume . $directory;
}

my $base_dir = getcwd();
my $self_dir = getdir(abs_path($0));

my $build_dir = File::Spec->catdir($base_dir, '.taglib-build');
my $install_dir = File::Spec->catdir($base_dir, '.taglib');

mkdir $build_dir;
chdir $build_dir or die "$!";

my $taglib_config = {
    use_git => 0,
    use_cmake => 0,
};

my $taglib_version_str = shift @ARGV;

my ($taglib_major_ver, $taglib_minor_ver) = split(/\./, $taglib_version_str);

$taglib_major_ver =~ s/^0+//;
$taglib_minor_ver =~ s/^0+//;

if(length($taglib_major_ver) == 0) {
    $taglib_major_ver = '0';
}

if(length($taglib_minor_ver) == 0) {
    $taglib_minor_ver = '0';
}

$taglib_major_ver += 0;
$taglib_minor_ver += 0;

if($taglib_major_ver >= 2) {
    $taglib_config->{'use_git'} = 1;
}

if($taglib_major_ver >= 2 or $taglib_minor_ver >= 7) {
    $taglib_config->{'use_cmake'} = 1;
}

if($taglib_config->{'use_git'}) {
    sys('git','clone','--depth','1','--branch','v'.$taglib_version_str,'https://github.com/taglib/taglib.git', 'taglib-' . $taglib_version_str);
    chdir('taglib-' . $taglib_version_str);
    if($taglib_major_ver >= 2) {
        sys('git', 'submodule', 'update', '--init', '--recursive');
    }
} else {
    sys('curl', '-RsSLO', 'https://taglib.org/releases/taglib-' . $taglib_version_str . '.tar.gz');
    sys('tar', 'xf', 'taglib-' . $taglib_version_str . '.tar.gz');
    chdir('taglib-' . $taglib_version_str);
}

my $patchfile = File::Spec->catfile($self_dir, 'patches', 'taglib-' . $taglib_version_str . '.patch');
if(-e $patchfile) {
    sys('patch', '-Np1', '-i', $patchfile);
}

if($taglib_config->{'use_cmake'}) {
    my @args = ('cmake', '-DCMAKE_INSTALL_PREFIX=' . $install_dir, '-B', 'build');
    if($taglib_major_ver == 1) {
        push(@args, '-DWITH_MP4=on', '-DWITH_ASF=on');
    }
    push(@args, '.');
    sys(@args);
    chdir('build');
} else {
    my @args = ('./configure', '--prefix', $install_dir, '--enable-shared', '--disable-static');
    if($taglib_major_ver == 1 and $taglib_minor_ver >= 6) {
        push(@args, '--enable-mp4', '--enable-asf');
    }
    sys(@args);
}

sys('make');
sys('make','install');
