# array
[1].class
[1].methods.include?(:[])

# hashtable
numbers = {1 => 'one', 2 => 'two'}
numbers[1]
numbers[2]
stuff = {:array => [1, 2, 3], :string => 'Hi, mom!'}    # symbol
stuff[:string]

# function
def tell_the_truth(options={})
    if options[:profession] == :lawyer
        'it could be believed that this is almost certainly not false.'
    else
        true
    end
end
tell_the_truth
tell_the_truth :profession => :lawyer

# class
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

# mixin
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

# some array functions
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
