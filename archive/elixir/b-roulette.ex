defmodule Main do
  def main do
    people = IO.gets("") |> String.trim() |> String.to_integer()

    bets =
      Enum.map(
        1..people,
        fn _ ->
          # ignore the length of the array
          IO.gets("")
          IO.gets("") |> String.trim() |> String.split(" ") |> Enum.map(&String.to_integer/1)
        end
      )

    x = IO.gets("") |> String.trim() |> String.to_integer()

    m =
      bets
      |> Enum.reduce(101, fn bet, m ->
        cond do
          length(bet) < m && Enum.member?(bet, x) -> length(bet)
          true -> m
        end
      end)

    answer =
      bets
      |> Enum.with_index()
      |> Enum.reduce([], fn t, acc ->
        {bet, i} = t

        cond do
          length(bet) == m && Enum.member?(bet, x) -> acc ++ [i + 1]
          true -> acc
        end
      end)

    IO.puts(length(answer))
    IO.puts(Enum.join(answer, " "))
  end
end
