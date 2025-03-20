IO.puts(inspect(Enum.all?(["foo", "bar", "hello"], fn x -> String.length(x) == 3 end)))
IO.puts(inspect(Enum.any?(["foo", "bar", "hello"], fn x -> String.length(x) == 3 end)))
# chunk divides the list into sublists
# [[1, 2], [3, 4], [5, 6]]
IO.puts(inspect(Enum.chunk_every([1, 2, 3, 4, 5, 6], 2)))
IO.puts(inspect(Enum.chunk_by(["foo", "bar", "helo", "elho"], fn x -> String.length(x) end)))
IO.puts(inspect(Enum.map_every([1, 2, 3, 4, 5, 6], 2, fn x -> 2 * x end)))
Enum.each([1, 2, 3, 4, 5, 6], fn x -> IO.puts(x) end)
IO.puts(inspect(Enum.map([1, 2, 3, 4, 5, 6], fn x -> 2 * x end)))
IO.puts(inspect(Enum.min([1, 2, 3, 4, 5, 6])))
IO.puts(inspect(Enum.max([1, 2, 3, 4, 5, 6])))
IO.puts(inspect(Enum.filter([1, 2, 3, 4, 5, 6], fn x -> rem(x, 2) == 0 end)))
IO.puts(inspect(Enum.reduce([1, 2, 3, 4, 5, 6], 0, fn x, acc -> x + acc end)))
IO.puts(inspect(Enum.sort([4, 1])))
IO.puts(inspect(Enum.sort([%{:val => 4}, %{:val => 1}], fn x, y -> x[:val] > y[:val] end)))
# & is a capture operator
IO.puts(inspect(Enum.map([1, 2, 3, 4, 5, 6], &(&1 + 3))))
