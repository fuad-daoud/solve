defmodule Main do
  @pi "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"

  def main do
    pre = IO.gets("") |> String.trim() |> String.to_integer()

    @pi
    |> String.slice(0, pre + 2)
    |> IO.puts()
  end
end
