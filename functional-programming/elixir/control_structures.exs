num = 2
if num == 2 do
  IO.puts("Number is 2")
else
  IO.puts("Number is not 2")
end

unless num == 2 do
  IO.puts("Number is not 2")
else
  IO.puts("Number is 2")
end

case num do
  1 -> IO.puts("Number is 1")
  2 -> IO.puts("Number is 2")
  _ -> IO.puts("Number is neither 1 nor 2")
end

cond do
  num == 1 -> IO.puts("Number is 1")
  num == 2 -> IO.puts("Number is 2")
  true -> IO.puts("Number is neither 1 nor 2")
end

with {:ok, a} <- {:ok, 1},
     {:ok, b} <- {:ok, 2},
     {:ok, c} <- {:ok, 3} do
  IO.puts("a: #{a}, b: #{b}, c: #{c}")
else
  _ -> IO.puts("Something went wrong")
end

