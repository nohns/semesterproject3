/** @format */

import React, { useState, useEffect } from "react";

interface CountdownProps {
  ms: number;
}
function Countdown({ ms }: CountdownProps): JSX.Element {
  const convertToSeconds = (ms: number) => {
    return ms / 1000;
  };

  const [count, setCount] = useState(convertToSeconds(ms));

  useEffect(() => {
    const interval = setInterval(() => {
      if (count > 0) {
        setCount(count - 1);
      } else {
        clearInterval(interval); // Stop the countdown when it reaches 0
      }
    }, 1000); // Update the countdown every 1 second

    return () => {
      clearInterval(interval); // Clean up the interval when the component unmounts
    };
  }, [count]);

  return (
    <div>
      <h1 className="scroll-m-20 text-white mt-10 text-8xl font-extrabold z-10 tracking-tight lg:text-5xl border-white">
        {count}
      </h1>
    </div>
  );
}

export default Countdown;
