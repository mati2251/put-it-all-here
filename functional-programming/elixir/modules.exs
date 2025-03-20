## import all functions and macros
# import Enum
## import with filter
# import List, only: [flatten: 1]
## require (import only macros)
# require Logger

defmodule MyVery.CoolModule do
  def my_function do
    IO.puts("Hello World")
  end
end

defmodule MyVery.UncoolModule do
  defmacro __using__(_) do
    quote do
      def uncool_function do
        IO.puts("I am uncool")
      end
    end
  end
end

defmodule MyModule do
  # alias for MyVery.CoolModule
  alias MyVery.CoolModule, as: Cool
  use MyVery.UncoolModule
  @moduledoc """
  This is a module documentation
  """
  @constant "I am a constant"

  @doc "will print the constant value"
  def my_function do
    IO.puts(@constant)
    Cool.my_function()
    uncool_function()
  end

  # derive (protected)
  @derive {Inspect, only: [:name, :age]}

  # defstruct
  defstruct name: "John", age: 0, belives: ""
end

MyModule.my_function()
