defmodule Main do
  def main do
    %{answer: answer} =
      IO.gets("")
      |> String.trim()
      |> String.to_charlist()
      |> Enum.with_index()
      |> Enum.reduce(%{window: [], indices: [], answer: 0}, fn {char, index},
                                                               %{
                                                                 window: window,
                                                                 indices: indices,
                                                                 answer: answer
                                                               } ->
        indices =
          cond do
            char == ?A && length(window) -> [index]
            char == ?A && List.first(window) == ?A -> [index]
            char == ?B && List.first(window) == ?A -> [index | indices]
            char == ?C && List.first(window) == ?B -> [index | indices]
            true -> []
          end

        window =
          cond do
            char == ?A && length(window) -> [char]
            char == ?A && List.first(window) == ?A -> [char]
            char == ?B && List.first(window) == ?A -> [char | window]
            char == ?C && List.first(window) == ?B -> [char | window]
            true -> []
          end

        answer =
          cond do
            length(indices) == 3 ->
              answer + 1

            true ->
              answer
          end

        window =
          cond do
            length(indices) == 3 ->
              []

            true ->
              window
          end

        indices =
          cond do
            length(indices) == 3 ->
              []

            true ->
              indices
          end

        %{window: window, indices: indices, answer: answer}
      end)

    IO.puts(answer)
  end
end

Main.main()
