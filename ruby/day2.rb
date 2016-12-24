#!/usr/bin/ruby

#### Print an array with 16 numbers, 4 numbers at a time
a = *(1..16)

puts 'Printing using each:'
a.each_with_index do |val, index|
  print val
  if index % 4 == 3
    puts
  else
    print ' '
  end
end

puts
puts 'Printing using each_slice:'
a.each_slice(4) { |a| p a }


#### Tree initialization
puts
puts 'Tree initialization and printing'
class Tree
  attr_accessor :children, :node_name

  def initialize(args)
    if not args.empty?
      a = args.first
      @node_name = a[0]
      @children =
        if a[1].empty?
          []
        else
          a[1].collect {|k, v| Tree.new({k=>v})}
        end
    end
  end

  def visit_all(&block)
    visit &block
    children.each {|c| c.visit_all &block}
  end

  def visit(&block)
    block.call self
  end
end

tree = Tree.new({'grandpa' =>
  {
    'dad' =>
      {
        'child 1' => {},
        'child 2' => {}
      },
    'uncle' =>
      {
        'child 3' => {},
        'child 4' => {}
      }
  }
})
tree.visit_all {|node| puts node.node_name}

#### grep
puts
puts 'grep command'

def grep(filename, pattern)
  File.open(filename, 'r') do |f|
    f.each do |line|
      puts "#{f.lineno}:\t#{line}" if pattern === line
    end
  end
end

def grep2(filename, pattern)
  f = File.new(filename)
  f.each { |line| puts "#{f.lineno}:\t#{line}" if pattern === line }
end

grep2("day2.rb", /grep/)
