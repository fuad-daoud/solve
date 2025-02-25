defmodule Main do
  def main do
    case IO.gets("")
         |> String.trim()
         |> String.split(" ") do
      ["fine", "fine"] -> IO.puts(4)
      ["sick", "fine"] -> IO.puts(2)
      ["fine", "sick"] -> IO.puts(3)
      ["sick", "sick"] -> IO.puts(1)
    end
  end
end
