const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{.preferred_optimize_mode = .ReleaseSafe});

    const exe = b.addExecutable(.{
        .name = "main",
        .target = target,
        .optimize = optimize,
    });

    exe.addCSourceFile(.{
        .file = b.path("main.cpp"),
        .flags = &[_][]const u8{
            "-std=c++17",
            "-O3", // Explicit O3 optimization
            "-ffast-math",
            "-fomit-frame-pointer",
            "-funroll-loops",
            "-ftree-vectorize",
            "-fno-signed-zeros",
            "-fno-trapping-math",
            "-fno-math-errno",
            "-fno-rtti", // Disable runtime type information
            "-fno-exceptions", // Disable exception handling
            "-fstrict-aliasing", // Enable strict aliasing optimization
            "-fno-plt", // Avoid PLT
            "-fdata-sections", // Each data in its own section
            "-ffunction-sections", // Each function in its own section
            "-falign-functions=32", // More reasonable alignment
            "-falign-loops=32", // More reasonable alignment
            "-fprefetch-loop-arrays", // Enable prefetching in loops

            // LLVM-specific optimizations using your working syntax
            "-mllvm", "--inline-threshold=500", // Reduced from 1000 for faster build
            "-mllvm", "--unroll-threshold=100", // Reduced for faster build
            "-mllvm", "--vectorize-loops",
            "-mllvm", "--vectorize-slp",
            "-mllvm", "--asan-opt", // As per your working flags
            "-mllvm", "--keep-loops", // As per your working flags
            "-mllvm", "--enable-gvn-hoist",
            "-mllvm", "--slp-vectorize-hor=1", // As per your working flags
        },
    });

    exe.linkLibCpp();
    exe.want_lto = true; // Enable LTO regardless of build mode
    exe.root_module.strip = true;
    b.installArtifact(exe);
}
