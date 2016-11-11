#!/usr/bin/ruby

# Replace part of a string
puts "Hello World!".sub("Hello", "Hi")

# Find substring
puts 'Hello, Ruby.'.index("Ruby.")

# Print your name 10 times
10.times { puts "Qirong" }

# Print "This is sentence number 1." 10 times, number 1..10
(1..10).each { |i| puts "This is sentence number #{i}." }

# Number guess
num = rand(10)
puts "Guess?"

while true
    guess = gets().to_i
    if guess > num
        puts "Too large"
    elsif guess < num
        puts "Too small"
    else
        puts "Correct"
        break
    end 
end
