using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

public class Program {
    public static void Main() {
        foreach (var file in Directory.GetFiles("Source", "*.*", SearchOption.AllDirectories)) {
            if (!file.EndsWith(".cpp") && !file.EndsWith(".h")) continue;
            
            string relPath = file.Replace("\\", "/");
            string origText = GetOriginalText(relPath);
            if (origText == null) continue;
            
            string currText = File.ReadAllText(file);
            if (!currText.Contains("\uFFFD") && !currText.Contains(".3\"") && !currText.Contains(".3"")) {
                continue;
            }
            
            var origLines = origText.Split(new[] { "\r\n", "\n" }, StringSplitOptions.None);
            var currLines = currText.Split(new[] { "\r\n", "\n" }, StringSplitOptions.None);
            
            for (int i=0; i<currLines.Length; i++) {
                if (currLines[i].Contains("\uFFFD") || currLines[i].Contains(".3\"")) {
                    string stripped = currLines[i].TrimStart();
                    
                    bool replaced = false;
                    foreach (var oLine in origLines) {
                        string oStripped = oLine.TrimStart();
                        if (stripped.StartsWith("SoundManager::GetInstance()->PlaySE") && oStripped.StartsWith("SoundManager::GetInstance()->PlaySE")) {
                            currLines[i] = oLine;
                            replaced = true;
                            break;
                        }
                        if (stripped.StartsWith("DrawString") && oStripped.StartsWith("DrawString")) {
                            currLines[i] = oLine;
                            replaced = true;
                            break;
                        }
                    }
                    
                    if (!replaced && currLines[i].Contains("\uFFFD") && stripped.StartsWith("//")) {
                        if (i < origLines.Length && origLines[i].TrimStart().StartsWith("//")) {
                            currLines[i] = origLines[i];
                        }
                    }
                }
            }
            
            File.WriteAllText(file, string.Join("\r\n", currLines), new UTF8Encoding(true));
            Console.WriteLine("Fixed " + relPath);
        }
    }
    
    static string GetOriginalText(string path) {
        var psi = new ProcessStartInfo("git", "show HEAD:" + path) {
            RedirectStandardOutput = true,
            UseShellExecute = false,
            StandardOutputEncoding = Encoding.GetEncoding(28591) // raw bytes
        };
        var proc = Process.Start(psi);
        string raw = proc.StandardOutput.ReadToEnd();
        proc.WaitForExit();
        if (proc.ExitCode != 0) return null;
        
        byte[] bytes = Encoding.GetEncoding(28591).GetBytes(raw);
        if (bytes.Length >= 2 && bytes[0] == 0xFF && bytes[1] == 0xFE) return Encoding.Unicode.GetString(bytes, 2, bytes.Length - 2);
        if (bytes.Length >= 3 && bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF) return Encoding.UTF8.GetString(bytes, 3, bytes.Length - 3);
        return Encoding.GetEncoding(932).GetString(bytes);
    }
}
