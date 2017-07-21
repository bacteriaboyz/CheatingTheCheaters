#!/usr/bin/env ruby

abort("Usage: #{$0} L_inf_rad < in.vtk > out.vtk") unless ARGV.size == 1

F = /^(?:[+-]?\d+\.\d+(?:[Ee][+-]?\d+)?(?:\s+|$)){3}$/
R = ARGV[0].to_f

print $_ unless F =~ $_ && $_.split.map { |x| x.to_f.abs }.max > R while $stdin.gets
