defmodule Main do
  def main do
    IO.gets("")
    |> String.graphemes()
    |> Enum.map(fn
      "N" -> ?S
      "E" -> ?W
      "S" -> ?N
      "W" -> ?E
      c -> c
    end)
    |> IO.puts()
  end
end
