import { useState, useEffect } from "react"
import "./App.css"

interface Task {
  id: number
  text: string
  completed: boolean
}

function TodoApp() {
  const [tasks, setTasks] = useState<Task[]>([])
  const [taskText, setTaskText] = useState<string>("")

  useEffect(() => {
    // Fetch tasks from the API when the component mounts
    fetchTasks()
  }, [])

  const fetchTasks = async () => {
    try {
      const response = await fetch("/api/tasks") // Replace with your API endpoint
      if (!response.ok) {
        throw new Error("Failed to fetch tasks")
      }
      const data = await response.json()
      setTasks(data)
    } catch (error) {
      console.error(error)
    }
  }

  const addTask = async () => {
    if (taskText.trim() !== "") {
      try {
        const response = await fetch("/api/tasks", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ text: taskText }),
        })

        if (!response.ok) {
          throw new Error("Failed to add task")
        }

        const newTask = await response.json()
        setTasks([...tasks, newTask])
        setTaskText("")
      } catch (error) {
        console.error(error)
      }
    }
  }

  const removeTask = async (id: number) => {
    try {
      const response = await fetch(`/api/tasks/${id}`, {
        method: "DELETE",
      })

      if (!response.ok) {
        throw new Error("Failed to delete task")
      }

      const updatedTasks = tasks.filter((task) => task.id !== id)
      setTasks(updatedTasks)
    } catch (error) {
      console.error(error)
    }
  }

  const toggleComplete = async (id: number) => {
    const taskToUpdate = tasks.find((task) => task.id === id)

    if (taskToUpdate) {
      try {
        const response = await fetch(`/api/tasks/${id}`, {
          method: "PUT",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ completed: !taskToUpdate.completed }),
        })

        if (!response.ok) {
          throw new Error("Failed to update task")
        }

        const updatedTasks = tasks.map((task) =>
          task.id === id ? { ...task, completed: !task.completed } : task
        )

        setTasks(updatedTasks)
      } catch (error) {
        console.error(error)
      }
    }
  }

  return (
    <div>
      <h1>Todo List</h1>
      <div>
        <input
          type="text"
          placeholder="Add a task"
          value={taskText}
          onChange={(e) => setTaskText(e.target.value)}
        />
        <button onClick={addTask}>Add</button>
      </div>
      <ul>
        {tasks.map((task) => (
          <li key={task.id}>
            <input
              type="checkbox"
              checked={task.completed}
              onChange={() => toggleComplete(task.id)}
            />
            <span
              style={{
                textDecoration: task.completed ? "line-through" : "none",
              }}
            >
              {task.text}
            </span>
            <button onClick={() => removeTask(task.id)}>Remove</button>
          </li>
        ))}
      </ul>
    </div>
  )
}

export default TodoApp
