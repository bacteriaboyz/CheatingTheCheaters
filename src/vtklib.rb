def vtkData(filename)
    raw = File.readlines(filename)

    num = /\d+/.match(raw[4])[0].to_i

    points = raw[5, num].map { |x| x.split.map(&:to_f) }

    types = raw[8 + num, num].map(&:to_i)

    [num, points, types]
end
