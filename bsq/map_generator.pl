# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    map_generator.pl                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirokiurabe <hirokiurabe@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 22:05:32 by hirokiurabe       #+#    #+#              #
#    Updated: 2025/02/10 22:05:47 by hirokiurabe      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/perl
use warnings;
use strict;
die "program x y density" unless (scalar(@ARGV) == 3);
my ($x, $y, $density) = @ARGV;
print "$y.ox\n";
for (my $i = 0; $i < $y; $i++) {
    for (my $j = 0; $j < $x; $j++) {
        if (int(rand($y) * 2) < $density) {
            print "o";
        }
        else {
            print ".";
        }
    }
    print "\n";
}
