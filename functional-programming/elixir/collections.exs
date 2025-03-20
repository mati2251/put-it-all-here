lists = [3.14, :pie, "Apple", :pie] # linked lists include non unique elements 
IO.puts(inspect lists)
IO.puts(inspect [:fast | lists]) # add to the front of the list (fast)
IO.puts(inspect lists ++ [:slow]) # add to the end of the list (slow)
IO.puts(inspect lists ++ lists) # concatenate lists
IO.puts(inspect lists -- [:pie]) # remove elements from list
IO.puts(inspect lists) # lists is not modified
IO.puts(hd lists) # head of the list
IO.puts(inspect tl lists) # tail of the list
tuple = {3.14, :pie, "Apple", :pie} # tuples has memory contiguously allocated
IO.puts(inspect tuple)
keyword_list = [foo: "bar", hello: "world"] # keyword list
IO.puts(inspect keyword_list) # keyword is a special two element tuple, keys are atoms, keys are ordered, keys do not have to be unique
map = %{"foo" => "bar", "hello" => :world} # map 
IO.puts(inspect map) # map is a collection of key value pairs, keys can be any value, keys are unique, keys are unordered
IO.puts(inspect Map.put(map, :hello, "world")) # add element to map (map is immutable)

