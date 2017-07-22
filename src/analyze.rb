#!/usr/bin/env ruby

abort("Usage: #{$0} file.vtk radius x_max") unless ARGV.size == 3

require_relative 'vtklib.rb'

RESET = "\e[0m"
BOLD = "\e[1m"
RED = "\e[31m"
GREEN = "\e[32m"
SYMBOLS = %w(- \\ | /)

P = 200000

NAN = '??'

STEPS =
[
    'Processing VTK file',
    'Computing pairwise distances',
    'Building adjacency lists',
    'Counting degrees',
    'Computing clustering coefficients'
]

def progress(message, n)
    $stderr.print "\r#{RED}#{message}#{RESET}...#{SYMBOLS[n % SYMBOLS.size]}"
    $stderr.flush
end

def done(message)
    $stderr.puts "#\r#{message}...#{GREEN}#{BOLD}Done#{RESET}"
end

def info(param, n, d)
    if d.zero?
        "#{param} #{n}/0 #{NAN} #{NAN}"
    else
        g = n.gcd(d)
        "#{param} #{n}/#{d} #{n / g}/#{d / g} %.2e" % n.fdiv(d)
    end
end

R = ARGV[1].to_f
L = ARGV[2].to_f

def metric(a, b)
    d = a.zip(b).map { |x| (x[0] - x[1]).abs }

    d[0] = L - d[0] if d[0] > L / 2

    d[1] = L - d[1] if d[1] > L / 2

    Math.sqrt(d.map { |r| r ** 2 }.inject(&:+))
end

# Process VTK file

$stderr.print "#{RED}#{STEPS[0]}#{RESET}..."

num, points, types = vtkData(ARGV[0])

done(STEPS[0])

# Compute pairwise distances

dists = Array.new(num) { Array.new(num) }

c = -1

num.times.to_a.combination(2) do |i, j|
    progress(STEPS[1], c / P) if ((c += 1) % P).zero?
    dists[i][j] = dists[j][i] = metric(points[i], points[j])
end

done(STEPS[1])

# Build adjacency list

c = -1

adj = Array.new(num) do |n|
    progress(STEPS[2], c / P) if ((c += 1) % P).zero?
    dists[n].map.with_index { |d, i| !d.nil? && d <= R ? i : nil }.compact
end

done(STEPS[2])

# Count degrees

degs = Array.new(num - 1, 0)

c = -1

adj.each do |l|
    progress(STEPS[3], c / P) if ((c += 1) % P).zero?
    degs[l.size] += 1
end

done(STEPS[3])

# Output results

rcn = 0
rcd = 0     # Fully resistant

scn = 0
scd = 0     # Fully non-resistant

rpn = 0
rpd = 0     # Mostly resistant

spn = 0
spd = 0     # Mostly non-resistant

c = -1

adj.each.with_index do |l, n|
    l.combination(2) do |i, j|
        progress(STEPS[4], c / P) if ((c += 1) % P).zero?
        connected = adj[i].include?(j)

        case types[n] + types[i] + types[j]
        when 0
            scd += 1
            scn += 1 if connected
        when 1
            spd += 1
            spn += 1 if connected
        when 2
            rpd += 1
            rpn += 1 if connected
        when 3
            rcd += 1
            rcn += 1 if connected
        end
    end
end

done(STEPS[4])

w = IO.popen('column -t', 'w')

w.puts <<-EOS
Coef Rational Reduced Decimal
#{info('R_c', rcn, rcd)}
#{info('R_p', rpn, rpd)}
#{info('S_c', scn, scd)}
#{info('S_p', spn, spd)}
EOS

w.close

puts degs * ','
