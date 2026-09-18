import lc


def test_parse_cases_splits_on_blank_lines_and_reads_expected():
    text = '3\n=> ["((()))","()()()"]\n\n1\n=> ["()"]\n\n4\n'
    cases = lc.parse_cases(text)
    assert [c.inputs for c in cases] == [["3"], ["1"], ["4"]]
    assert [c.expected for c in cases] == ['["((()))","()()()"]', '["()"]', None]


def test_parse_cases_multi_arg_inputs():
    cases = lc.parse_cases("[2,7,11,15]\n9\n=> [0,1]\n")
    assert cases[0].inputs == ["[2,7,11,15]", "9"]
    assert cases[0].expected == "[0,1]"


def test_parse_cases_tilde_marks_unordered():
    cases = lc.parse_cases("[1,2]\n=> ~ [2,1]\n")
    assert cases[0].expected == "[2,1]"
    assert cases[0].unordered is True


def test_parse_cases_ignores_extra_blank_lines_and_comments():
    cases = lc.parse_cases("# first\n\n\n5\n\n\n\n# second\n6\n=> 1\n\n")
    assert [c.inputs for c in cases] == [["5"], ["6"]]


def test_compare_is_whitespace_insensitive_json():
    assert lc.matches("[0, 1]", [0, 1]) is True
    assert lc.matches("[0,1]", [1, 0]) is False


def test_compare_unordered_ignores_list_order():
    assert lc.matches("[3,1,2]", [1, 2, 3], unordered=True) is True
    assert lc.matches("[3,1,2]", [1, 2, 4], unordered=True) is False


def test_compare_floats_with_tolerance():
    assert lc.matches("0.33333", 1 / 3) is True
    assert lc.matches("0.5", 1 / 3) is False


def test_compare_invalid_expected_is_a_mismatch_not_a_crash():
    assert lc.matches("not json", 1) is False


class Solution:
    def twoSum(self, nums, target):
        seen = {}
        for i, n in enumerate(nums):
            if target - n in seen:
                return [seen[target - n], i]
            seen[n] = i
        return []


def test_find_method_picks_the_single_public_method():
    assert lc.find_method(Solution).__name__ == "twoSum"


def test_run_cases_reports_pass_fail_and_unchecked():
    cases = lc.parse_cases("[2,7,11,15]\n9\n=> [0,1]\n\n[3,2,4]\n6\n=> [0,0]\n\n[3,3]\n6\n")
    results = lc.run_cases(Solution, cases)
    assert [r.status for r in results] == ["pass", "fail", "unchecked"]
    assert results[1].actual == "[1,2]"
    assert results[2].actual == "[0,1]"


def test_run_cases_captures_exceptions_as_error():
    class Broken:
        def f(self, x):
            raise ValueError("boom")

    results = lc.run_cases(Broken, lc.parse_cases("1\n=> 1\n"))
    assert results[0].status == "error"
    assert "boom" in results[0].actual


HEADER = "# 22. Generate Parentheses [Medium]\n# https://leetcode.com/problems/generate-parentheses/\n\nclass Solution: ...\n"


def test_parse_header_reads_id_title_difficulty_slug():
    meta = lc.parse_header(HEADER)
    assert (meta.id, meta.title, meta.difficulty, meta.slug) == (22, "Generate Parentheses", "Medium", "generate-parentheses")


def test_parse_header_missing_raises():
    import pytest
    with pytest.raises(ValueError):
        lc.parse_header("class Solution: ...\n")


def test_slug_from_arg_accepts_url_or_slug():
    assert lc.slug_from_arg("https://leetcode.com/problems/two-sum/description/?envType=x") == "two-sum"
    assert lc.slug_from_arg("https://leetcode.com/problems/two-sum") == "two-sum"
    assert lc.slug_from_arg("two-sum") == "two-sum"


FETCHED = {
    "questionFrontendId": "22",
    "title": "Generate Parentheses",
    "titleSlug": "generate-parentheses",
    "difficulty": "Medium",
    "exampleTestcases": "3\n1",
    "metaData": '{"name":"generateParenthesis","params":[{"name":"n","type":"integer"}],"return":{"type":"list<string>"}}',
    "codeSnippets": [
        {"langSlug": "cpp", "code": "class Solution {};"},
        {"langSlug": "python3", "code": "class Solution:\n    def generateParenthesis(self, n: int) -> list[str]:\n        "},
    ],
    "content": '<p>Example 1:</p><pre><strong>Input:</strong> n = 3\n<strong>Output:</strong> [&quot;((()))&quot;,&quot;()()()&quot;]\n</pre><pre><strong>Input:</strong> n = 1\n<strong>Output:</strong> [&quot;()&quot;]\n</pre>',
}


def test_render_solve_has_header_snippet_and_harness():
    text = lc.render_solve(FETCHED)
    assert text.startswith("# 22. Generate Parentheses [Medium]\n# https://leetcode.com/problems/generate-parentheses/\n")
    assert "def generateParenthesis(self, n: int) -> list[str]:" in text
    assert lc.parse_header(text).id == 22
    assert 'if __name__ == "__main__":' in text


def test_render_cases_groups_examples_by_arity_with_expected():
    assert lc.render_cases(FETCHED) == '3\n=> ["((()))","()()()"]\n\n1\n=> ["()"]\n'


def test_render_cases_without_outputs_leaves_expected_off():
    data = dict(FETCHED, content="<p>no examples</p>", exampleTestcases="[1,2]\n5\n[3]\n6",
                metaData='{"name":"f","params":[{"name":"a"},{"name":"b"}]}')
    assert lc.render_cases(data) == "[1,2]\n5\n\n[3]\n6\n"


def test_format_report_shows_failures_and_summary():
    cases = lc.parse_cases("[2,7,11,15]\n9\n=> [0,1]\n\n[3,2,4]\n6\n=> [0,0]\n\n[3,3]\n6\n")
    report = lc.format_report(lc.run_cases(Solution, cases))
    assert "Case 1  ✓" in report
    assert "Case 2  ✗" in report
    assert "expected: [0,0]" in report
    assert "got:      [1,2]" in report
    assert "Case 3  ·" in report
    assert report.rstrip().endswith("1 passed, 1 failed, 1 unchecked")


def test_save_copies_solve_and_cases_and_updates_readme(tmp_path):
    (tmp_path / "solve.py").write_text(HEADER)
    (tmp_path / "cases.txt").write_text("3\n=> 1\n")
    (tmp_path / "README.md").write_text("# Solve\n\n<!-- problems -->\nold\n<!-- /problems -->\n")
    (tmp_path / "problems").mkdir()
    (tmp_path / "problems" / "0001-two-sum.py").write_text("# 1. Two Sum [Easy]\n# https://leetcode.com/problems/two-sum/\n")
    (tmp_path / "problems" / "0006-zigzag-conversion.py").write_text("# no header, legacy file\n")

    written = lc.save(tmp_path)

    assert (tmp_path / "problems" / "0022-generate-parentheses.py").read_text() == HEADER
    assert (tmp_path / "problems" / "0022-generate-parentheses.cases.txt").read_text() == "3\n=> 1\n"
    assert written == [tmp_path / "problems" / "0022-generate-parentheses.py",
                       tmp_path / "problems" / "0022-generate-parentheses.cases.txt",
                       tmp_path / "README.md"]
    readme = (tmp_path / "README.md").read_text()
    assert "old" not in readme
    assert "| 1 | [Two Sum](https://leetcode.com/problems/two-sum/) | Easy | [0001-two-sum.py](problems/0001-two-sum.py) |" in readme
    assert "| 6 | [zigzag-conversion](https://leetcode.com/problems/zigzag-conversion/) |  | [0006-zigzag-conversion.py](problems/0006-zigzag-conversion.py) |" in readme
    assert "| 22 | [Generate Parentheses]" in readme
    assert readme.index("| 1 |") < readme.index("| 6 |") < readme.index("| 22 |")
    assert readme.startswith("# Solve\n\n<!-- problems -->\n")
    assert readme.endswith("<!-- /problems -->\n")


def test_save_skips_readme_without_markers(tmp_path):
    (tmp_path / "solve.py").write_text(HEADER)
    (tmp_path / "cases.txt").write_text("")
    (tmp_path / "README.md").write_text("# no markers\n")
    written = lc.save(tmp_path)
    assert (tmp_path / "README.md").read_text() == "# no markers\n"
    assert tmp_path / "README.md" not in written


def test_start_writes_solve_and_cases(tmp_path, monkeypatch):
    monkeypatch.setattr(lc, "fetch", lambda slug: dict(FETCHED, titleSlug=slug))
    lc.start(tmp_path, "https://leetcode.com/problems/generate-parentheses/")
    assert lc.parse_header((tmp_path / "solve.py").read_text()).id == 22
    assert (tmp_path / "cases.txt").read_text() == '3\n=> ["((()))","()()()"]\n\n1\n=> ["()"]\n'


def test_start_refuses_to_clobber_unsaved_other_problem(tmp_path, monkeypatch):
    import pytest
    monkeypatch.setattr(lc, "fetch", lambda slug: FETCHED)
    (tmp_path / "solve.py").write_text("# 1. Two Sum [Easy]\n# https://leetcode.com/problems/two-sum/\nclass Solution: pass\n")
    (tmp_path / "cases.txt").write_text("")
    with pytest.raises(lc.Unsaved):
        lc.start(tmp_path, "generate-parentheses")
    assert lc.parse_header((tmp_path / "solve.py").read_text()).id == 1


def test_start_overwrites_when_current_problem_is_saved(tmp_path, monkeypatch):
    monkeypatch.setattr(lc, "fetch", lambda slug: FETCHED)
    two_sum = "# 1. Two Sum [Easy]\n# https://leetcode.com/problems/two-sum/\nclass Solution: pass\n"
    (tmp_path / "solve.py").write_text(two_sum)
    (tmp_path / "problems").mkdir()
    (tmp_path / "problems" / "0001-two-sum.py").write_text(two_sum)
    lc.start(tmp_path, "generate-parentheses")
    assert lc.parse_header((tmp_path / "solve.py").read_text()).id == 22


def test_start_overwrites_same_problem_with_force(tmp_path, monkeypatch):
    monkeypatch.setattr(lc, "fetch", lambda slug: FETCHED)
    (tmp_path / "solve.py").write_text(HEADER + "# edited\n")
    lc.start(tmp_path, "generate-parentheses", force=True)
    assert "# edited" not in (tmp_path / "solve.py").read_text()


def test_add_appends_case_block(tmp_path):
    (tmp_path / "cases.txt").write_text("3\n=> 1\n")
    lc.add(tmp_path, inputs=["[1,2]", "5"], expected="[0]")
    assert (tmp_path / "cases.txt").read_text() == "3\n=> 1\n\n[1,2]\n5\n=> [0]\n"
    lc.add(tmp_path, inputs=["7"], expected=None)
    assert (tmp_path / "cases.txt").read_text().endswith("\n\n7\n")


def test_load_solution_imports_solve_py(tmp_path):
    (tmp_path / "solve.py").write_text(HEADER.replace("class Solution: ...", "class Solution:\n    def f(self, n): return n * 2"))
    cls = lc.load_solution(tmp_path)
    assert cls().f(4) == 8


def test_main_test_exit_code_reflects_failures(tmp_path, capsys):
    (tmp_path / "solve.py").write_text("class Solution:\n    def f(self, n): return n * 2\n")
    (tmp_path / "cases.txt").write_text("2\n=> 4\n\n3\n=> 7\n")
    assert lc.main(["test"], root=tmp_path) == 1
    assert "1 passed, 1 failed" in capsys.readouterr().out
    (tmp_path / "cases.txt").write_text("2\n=> 4\n")
    assert lc.main(["test"], root=tmp_path) == 0


def test_main_reports_missing_files_without_traceback(tmp_path, capsys):
    assert lc.main(["save"], root=tmp_path) == 1
    assert lc.main(["test"], root=tmp_path) == 1
    err = capsys.readouterr().err
    assert "solve.py" in err and "Traceback" not in err


def test_main_test_reports_syntax_error_in_solve_briefly(tmp_path, capsys):
    (tmp_path / "solve.py").write_text("class Solution:\n    def f(self, n):\n\n\nx = 1\n")
    (tmp_path / "cases.txt").write_text("1\n")
    assert lc.main(["test"], root=tmp_path) == 1
    err = capsys.readouterr().err
    assert err == "lc: solve.py line 2: expected an indented block after function definition\n"


def test_render_cases_marks_unordered_when_problem_says_any_order():
    data = dict(FETCHED, content="<p>Return the answer in <strong>any order</strong>.</p>" + FETCHED["content"])
    assert lc.render_cases(data) == '3\n=> ~ ["((()))","()()()"]\n\n1\n=> ~ ["()"]\n'


ROADMAP = (
    "- [ ] **242. Valid Anagram** (Easy) · [LC](https://leetcode.com/problems/valid-anagram/) · [Video](https://youtu.be/a)\n"
    "- [ ] **22. Generate Parentheses** (Medium) · [LC](https://leetcode.com/problems/generate-parentheses/) · [Video](https://youtu.be/b)\n"
)


def test_update_roadmap_ticks_and_links_the_saved_problem(tmp_path):
    (tmp_path / "ROADMAP.md").write_text(ROADMAP)
    assert lc.update_roadmap(tmp_path, lc.parse_header(HEADER)) is True
    lines = (tmp_path / "ROADMAP.md").read_text().splitlines()
    assert lines[0] == ROADMAP.splitlines()[0]
    assert lines[1] == "- [x] **22. Generate Parentheses** (Medium) · [LC](https://leetcode.com/problems/generate-parentheses/) · [Video](https://youtu.be/b) · [sol](problems/0022-generate-parentheses.py)"


def test_update_roadmap_is_idempotent(tmp_path):
    (tmp_path / "ROADMAP.md").write_text(ROADMAP)
    lc.update_roadmap(tmp_path, lc.parse_header(HEADER))
    once = (tmp_path / "ROADMAP.md").read_text()
    assert lc.update_roadmap(tmp_path, lc.parse_header(HEADER)) is False
    assert (tmp_path / "ROADMAP.md").read_text() == once


def test_update_roadmap_false_when_problem_not_listed_or_no_file(tmp_path):
    assert lc.update_roadmap(tmp_path, lc.parse_header(HEADER)) is False
    (tmp_path / "ROADMAP.md").write_text(ROADMAP.splitlines()[0] + "\n")
    assert lc.update_roadmap(tmp_path, lc.parse_header(HEADER)) is False


def test_save_includes_roadmap_when_it_changed(tmp_path):
    (tmp_path / "solve.py").write_text(HEADER)
    (tmp_path / "cases.txt").write_text("")
    (tmp_path / "ROADMAP.md").write_text(ROADMAP)
    assert tmp_path / "ROADMAP.md" in lc.save(tmp_path)
    assert tmp_path / "ROADMAP.md" not in lc.save(tmp_path)


def test_render_cases_reads_span_style_outputs():
    data = dict(FETCHED, exampleTestcases='"anagram"\n"nagaram"\n"rat"\n"car"',
                metaData='{"name":"isAnagram","params":[{"name":"s"},{"name":"t"}]}',
                content='<p><strong>Input:</strong> <span class="example-io">s = "anagram"</span></p>'
                        '<p><strong>Output:</strong> <span class="example-io">true</span></p>'
                        '<p><strong>Output:</strong> <span class="example-io">[1,2]</span></p>')
    assert lc.render_cases(data) == '"anagram"\n"nagaram"\n=> true\n\n"rat"\n"car"\n=> [1,2]\n'


def test_html_to_markdown_paragraphs_code_bold_and_entities():
    md = lc.html_to_markdown('<p>Given <code>s</code>, return <strong>true</strong> if &quot;x&quot; &lt; y.</p>\n\n<p>&nbsp;</p>\n<p>Next.</p>')
    assert md == 'Given `s`, return **true** if "x" < y.\n\nNext.\n'


def test_html_to_markdown_pre_becomes_fenced_block_and_sup_caret():
    md = lc.html_to_markdown('<pre><strong>Input:</strong> n = 3\n<strong>Output:</strong> [1]\n</pre><ul>\n\t<li><code>1 &lt;= n &lt;= 10<sup>4</sup></code></li>\n</ul>')
    assert md == "```\nInput: n = 3\nOutput: [1]\n```\n\n- `1 <= n <= 10^4`\n"


def test_html_to_markdown_example_io_spans_and_em():
    md = lc.html_to_markdown('<p><strong class="example">Example 1:</strong></p><div class="example-block"><p><strong>Input:</strong> <span class="example-io">s = &quot;a&quot;</span></p><p><strong>Output:</strong> <span class="example-io">true</span></p></div><p><em>note</em></p>')
    assert md == '**Example 1:**\n\n**Input:** s = "a"\n\n**Output:** true\n\n*note*\n'


def test_render_problem_has_title_line_then_body():
    md = lc.render_problem(FETCHED)
    assert md.startswith("# 22. Generate Parentheses [Medium]\n\nhttps://leetcode.com/problems/generate-parentheses/\n\n")
    assert 'Output: ["((()))","()()()"]' in md


def test_start_writes_problem_md(tmp_path, monkeypatch):
    monkeypatch.setattr(lc, "fetch", lambda slug: FETCHED)
    lc.start(tmp_path, "generate-parentheses")
    assert (tmp_path / "problem.md").read_text().startswith("# 22. Generate Parentheses")


def test_commit_message_from_header():
    assert lc.commit_message(lc.parse_header(HEADER)) == "feat: solved 22. Generate Parentheses [Medium]"


def test_commit_stages_working_files_and_commits(tmp_path):
    import subprocess
    git = lambda *a: subprocess.run(["git", *a], cwd=tmp_path, check=True, capture_output=True, text=True).stdout
    git("init", "-q")
    git("config", "user.email", "t@t"); git("config", "user.name", "t")
    (tmp_path / "solve.py").write_text(HEADER)
    (tmp_path / "cases.txt").write_text("3\n")
    (tmp_path / "problem.md").write_text("# 22\n")
    (tmp_path / "unrelated.txt").write_text("x\n")
    assert lc.main(["commit"], root=tmp_path) == 0
    assert git("log", "--format=%s", "-1").strip() == "feat: solved 22. Generate Parentheses [Medium]"
    assert set(git("show", "--name-only", "--format=", "HEAD").split()) == {"solve.py", "cases.txt", "problem.md"}
    assert "unrelated.txt" in git("status", "--porcelain")


def test_next_unsolved_is_first_unticked_roadmap_url(tmp_path):
    (tmp_path / "ROADMAP.md").write_text(
        "- [x] **217. Contains Duplicate** (Easy) · [LC](https://leetcode.com/problems/contains-duplicate/) · [Video](https://youtu.be/a)\n"
        "- [ ] **49. Group Anagrams** (Medium) · [LC](https://leetcode.com/problems/group-anagrams/) · [Video](https://youtu.be/b)\n"
        "- [ ] **347. Top K** (Medium) · [LC](https://leetcode.com/problems/top-k-frequent-elements/) · [Video](https://youtu.be/c)\n")
    assert lc.next_unsolved(tmp_path) == "https://leetcode.com/problems/group-anagrams/"


def test_next_unsolved_none_when_done_or_missing(tmp_path):
    assert lc.next_unsolved(tmp_path) is None
    (tmp_path / "ROADMAP.md").write_text("- [x] **1. Two Sum** (Easy) · [LC](https://leetcode.com/problems/two-sum/)\n")
    assert lc.next_unsolved(tmp_path) is None


def test_main_next_starts_the_next_roadmap_problem(tmp_path, monkeypatch, capsys):
    seen = []
    monkeypatch.setattr(lc, "fetch", lambda slug: seen.append(slug) or FETCHED)
    (tmp_path / "ROADMAP.md").write_text("- [ ] **22. Generate Parentheses** (Medium) · [LC](https://leetcode.com/problems/generate-parentheses/)\n")
    assert lc.main(["next"], root=tmp_path) == 0
    assert seen == ["generate-parentheses"]
    assert (tmp_path / "solve.py").exists()


def test_main_next_reports_when_roadmap_is_complete(tmp_path, capsys):
    (tmp_path / "ROADMAP.md").write_text("- [x] **1. Two Sum** (Easy) · [LC](https://leetcode.com/problems/two-sum/)\n")
    assert lc.main(["next"], root=tmp_path) == 1
    assert "ROADMAP" in capsys.readouterr().err


def test_compare_unordered_is_recursive_into_nested_lists():
    assert lc.matches('[["bat"],["nat","tan"],["ate","eat","tea"]]', [["tea", "ate", "eat"], ["tan", "nat"], ["bat"]], unordered=True) is True
    assert lc.matches('[["bat"],["nat","tan"]]', [["bat", "nat"], ["tan"]], unordered=True) is False
