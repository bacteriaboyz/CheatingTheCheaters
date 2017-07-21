#!/usr/bin/env ruby

abort("Usage: #{$0} in.vtk L_inf_rad x_max") unless ARGV.size == 3

require_relative 'vtklib.rb'

CUTOFF = ARGV[1].to_f / 2
RADIUS = ARGV[2].to_f / 2

num, points, types = vtkData(ARGV[0])

points, types = points.zip(types).reject do |p, t|
    p[0..1].map { |c| (c - RADIUS).abs }.max > CUTOFF
end.transpose

points.map! { |p| "%.6e %.6e %.6e" % p }

puts <<-EOS
# vtk DataFile Version 2.0
#{File.basename(ARGV[0])}
ASCII
DATASET POLYDATA
POINTS #{points.size} float
#{points * "\n"}
POINT_DATA #{points.size}
SCALARS enzyme float
LOOKUP_TABLE Producers
#{types * "\n"}
EOS
