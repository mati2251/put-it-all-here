# pin operator
a = 1
%{^a => b} = %{1 => "Pattern matching"}
IO.puts(b)
defmodule MyList do
  def sum([]), do: 0
  def sum([head | tail]), do: head + sum(tail)
end

IO.puts("List sum #{MyList.sum([1, 2, 3, 4, 5])}")

[a, b, c] = [1, 2, 3]
IO.puts("a: #{a}, b: #{b}, c: #{c}")
[head | tail] = [1, 4, 5]
IO.puts("head: #{head}, tail: " <> inspect(tail))

defmodule FibonaciMod do 
  def fib(0), do: 0
  def fib(1), do: 1
  def fib(n), do: fib(n - 1) + fib(n - 2)
end

defmodule Power do
  def pow(0, _), do: 1
  def pow(_, 0), do: 1
  def pow(x, y), do: x * pow(x, y - 1)
end

IO.puts("Fibonaci 10: #{FibonaciMod.fib(10)}")

listA = [1, 2, 3, 4, 5]

listA |> MyList.sum |> FibonaciMod.fib |> Power.pow(2) |> IO.puts

IO.puts("Anonymous function")

Enum.map [1, 2, 3, 4, 5], fn x -> x * x end |> IO.inspect
Enum.map [1, 2, 3, 4, 5], &(&1 * &1) |> IO.inspect

IO.puts("Named function")

defmodule MyEnum do
  def square(x), do: x * x
end

Enum.map [1, 2, 3, 4, 5], &MyEnum.square(&1) |> IO.inspect
Enum.map 0..10, &FibonaciMod.fib(&1) |> IO.inspect

defmodule MyGuard do
  def is_even(x) when rem(x, 2) == 0, do: true
  def is_even(_), do: false
end

defmodule DefaultArgs do
  def greet(name \\ "world"), do: "Hello, #{name}"
end
