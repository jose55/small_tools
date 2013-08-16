#!/bin/perl
# use strict and warnings for a proper code
use strict;
use warnings;


my ($begin, $end) = (1, 1000);
# Parse command line options if given
if (@ARGV) {
	$begin = $ARGV[0];
	$end = $ARGV[1];
}

# running variables
my $isprime = 1;
my ($i, $n);

# This for loop starts at the lower bondary, and counts +1 until the upper bondary is reached
for ($n = $begin; $n <= $end; $n++) {

	# A prime can only be divided by 1 and itself (so I test all numbers between 2 and n-1)
	for ($i = 2; $i < $n; $i++) {
	
		# Calculate modulo to test if number is a prime.
		if ($n % $i == 0) {
			# If n modulo any other number is true only once, n can't be a prime.
			$isprime = 0;
			# leave the loop (no need to test other numbers)
			last;
		}
	}
	
	# only print prime numbers.
	if ($isprime) {
		print "$n\n";
	}
	
	# reset the boolean for the next number.
	$isprime = 1;
}
