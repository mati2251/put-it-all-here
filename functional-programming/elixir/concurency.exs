pid =
  spawn(fn ->
    IO.puts("Hello from first process #{inspect(self())}")

    receive do
      {pid2, msg} ->
        IO.puts("Received #{msg}")
        send(pid2, "Hello from first process")
    end
  end)

fn ->
  IO.puts("Hello from second process #{inspect(self())}")
  send(pid, {self(), "Hello from second process"})

  receive do
    msg -> IO.puts("Received #{msg}")
  end
end
|> spawn

IO.puts("Hello from main process #{inspect(self())}")

translate = fn ->
  receive do
    {from_pid, :en} ->
      send(from_pid, "Hello")

    {from_pid, :es} ->
      send(from_pid, "Hola")

    {from_pid, :fr} ->
      send(from_pid, "Bonjour")

    {from_pid, :pl} ->
      send(from_pid, "Cześć")
  end
end

Process.flag(:trap_exit, true)
pid = translate |> spawn_link

send(pid, {self(), :pl})

receive do
  msg -> IO.puts("Received #{msg}")
end

send(pid, {self(), :fr})

receive do
  msg -> IO.puts("Received #{inspect msg}")
end


