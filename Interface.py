import tkinter as tk
from tkinter import messagebox

class ObjectMap:
    def __init__(self, root):
        self.root = root
        self.root.title("Object Map GUI")
        self.objects = []

        self.canvas = tk.Canvas(root, width=400, height=400, bg="white")
        self.canvas.pack()

        frame = tk.Frame(root)
        frame.pack()

        tk.Label(frame, text="X:").grid(row=0, column=0)
        tk.Label(frame, text="Y:").grid(row=1, column=0)

        self.x_entry = tk.Entry(frame)
        self.y_entry = tk.Entry(frame)
        self.x_entry.grid(row=0, column=1)
        self.y_entry.grid(row=1, column=1)

        tk.Button(frame, text="Add Object", command=self.add_object).grid(row=2, column=0, columnspan=2)
        tk.Button(frame, text="Remove Object", command=self.remove_object).grid(row=3, column=0, columnspan=2)
        tk.Button(frame, text="Clear All", command=self.clear_objects).grid(row=4, column=0, columnspan=2)

    def add_object(self):
        try:
            x = int(self.x_entry.get())
            y = int(self.y_entry.get())
            self.objects.append((x, y))
            self.canvas.create_oval(x-5, y-5, x+5, y+5, fill="red", tags=f"obj_{x}_{y}")
        except ValueError:
            messagebox.showerror("Error", "Invalid coordinates")

    def remove_object(self):
        try:
            x = int(self.x_entry.get())
            y = int(self.y_entry.get())
            if (x, y) in self.objects:
                self.objects.remove((x, y))
                self.canvas.delete(f"obj_{x}_{y}")
            else:
                messagebox.showwarning("Warning", "Object not found")
        except ValueError:
            messagebox.showerror("Error", "Invalid coordinates")

    def clear_objects(self):
        self.objects.clear()
        self.canvas.delete("all")

if __name__ == "__main__":
    root = tk.Tk()
    app = ObjectMap(root)
    root.mainloop()
