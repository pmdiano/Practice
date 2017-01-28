- array
```ruby
[1].class
[1].methods.include?(:[])
```

- hashtable
```ruby
numbers = {1 => 'one', 2 => 'two'}
numbers[1]
numbers[2]
stuff = {:array => [1, 2, 3], :string => 'Hi, mom!'}    # symbol
stuff[:string]
```

- function
```ruby
def tell_the_truth(options={})
    if options[:profession] == :lawyer
        'it could be believed that this is almost certainly not false.'
    else
        true
    end
end
tell_the_truth
tell_the_truth :profession => :lawyer
```

- class
```ruby
class Tree
  attr_accessor :children, :node_name

  def initialize(name, children=[])
    @children = children
    @node_name = name
  end

  def visit_all(&block)
    visit &block
    children.each {|c| c.visit_all &block}
  end

  def visit(&block)
    block.call self
  end
end

ruby_tree = Tree.new("Ruby", [Tree.new("Reia"), Tree.new("MacRuby")])

puts "Visiting a node"
ruby_tree.visit {|node| puts node.node_name}
puts

puts "Visiting entire tree"
ruby_tree.visit_all {|node| puts node.node_name}
```

- mixin
```ruby
module ToFile
  def filename
    "object_#{self.object_id}.txt"
  end

  def to_f
    File.open(filename, 'w') {|f| f.write(to_s)}
  end
end
class Person
  include ToFile
  attr_accessor :name

  def initialize(name)
    @name = name
  end

  def to_s
    name
  end
end
```

- some array functions
```ruby
a = [5, 3, 4, 1]
a.sort
a.any? {|i| i > 6}
a.all? {|i| i > 0}
a.collect {|i| i * 2}
a.select {|i| i % 2 == 0}
a.member?(2)
a.inject {|sum, i| sum + i}
a.inject(0) do |sum, i|
  puts "sum: #{sum} i: #{i} sum + i: #{sum + i}"
  sum + i
end
```

- StringIO library
```ruby
require 'stringio'
out = StringIO()
puts out.string
```

- type checking
```ruby
if not obj.kind_of?(String)
  raise TypeError, "not a string"
end
```

- method checking
```ruby
if not obj.respond_to?("to_str")
  raise TypeError, "not a string"
end
```

- method_missing to implement Roman number!!
```ruby
class Roman
  def self.method_missing name, *args
    roman = name.to_s
    roman.gsub!("IV", "IIII")
    roman.gsub!("IX", "VIIII")
    roman.gsub!("XL", "XXXX")
    roman.gsub!("XC", "LXXXX")

    (roman.count("I") +
     roman.count("V") * 5 +
     roman.count("X") * 10 +
     roman.count("L") * 50 +
     roman.count("C") * 100)
  end
end

puts Roman.X
puts Roman.XII
```

- Regex and hash table
```ruby
date = {}
ARGF.each do |line|
  if /\d\d\/[A-Z][a-z][a-z]\/\d\d/ =~ line
    date[$&] ||= Hash.new(0)
    dic = date[$&]
    if /GET ([^ ]+) HTTP/ =~ line
      dic[$1] += 1
    end
  end
end
printf "%15s %s\n", "IP addr", "num"
date.keys.sort.each do |d|
  puts d
  date[d].sort_by{|k,v| -v}[0..2].each do |url, n|
    printf "%-25s %d\n", url, n
  end
end
```

- each_with_object and letter usage
```ruby
(0..23).each_with_object(foo) do |i, h|
  letter = (i+?c.ord).chr
end
```

- usage of STDIN and map function
```ruby
STDIN.each_line do |line|
  val = line
  year, temp, q = val[15,4], val[87,5], val[92,1]
  puts "#{year}\t#{temp}" if (temp != "+9999" && q =~ /[01459]/)
end
```

- reduce function
```ruby
last_key, max_val = nil, -1000000
STDIN.each_line do |line|
  key, val = line.split("\t")
  if last_key && last_key != key
    puts "#{last_key}\t#{max_val}"
    last_key, max_val = key, val.to_i
  else
    last_key, max_val = key, [max_val, val.to_i].max
  end
end
puts "#{last_key}\t#{max_val}" if last_key
```

- Prime number and step
```ruby
sieve = []
max = 100
for i in 2 .. max
  sieve[i] = i
end

for i in 2 .. Math.sqrt(max)
  next unless sieve[i]
  (i*i).step(max, i) do |j|
    sieve[j] = nil
  end
end

puts sieve.compact.join(", ")
```

- What is `$!`?
```ruby
begin
  opts.parse(ARGV)
  raise OptionParser::MissingArgument if some_parameter.nil?
  # Some other code
rescue OptionParser::InvalidOption, OptionParser::MissingArgument
  raise $!.to_s
end
```

- Ruby profiler: `ruby -rprofile`

- Benchmark module
```ruby
require 'benchmark'

a = (1..10000).collect{rand(1000)}
b = (1..10000).collect{rand(1000)}

Benchmark.bm do |x|
  x.report { intersect1(a, b) }
  x.report { intersect2(a, b) }
end
```
