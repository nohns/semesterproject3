/** @format */

//I need a component which tells what the clock is in the format: 20:44

import { useState, useEffect } from "react";

function Clock(): JSX.Element {
  const [time, setTime] = useState(new Date());

  useEffect(() => {
    const timer = setInterval(() => {
      setTime(new Date());
    }, 1000);

    return () => {
      clearInterval(timer);
    };
  }, []);

  return (
    <div className="text-sm font-medium leading-none text-muted-foreground">
      {time.getHours().toString().padStart(2, "0")}:
      {time.getMinutes().toString().padStart(2, "0")}
    </div>
  );
}

export default Clock;
