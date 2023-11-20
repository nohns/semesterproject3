/** @format */

import React, { useState, useEffect } from "react";
import { CountdownCircleTimer } from "react-countdown-circle-timer";

interface CountdownProps {
  time: number;
}

function Countdown({ time }: CountdownProps): JSX.Element {
  const [count, setCount] = useState(time / 1000);

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

  const renderTime = ({ remainingTime }: any) => {
    return (
      <div className="flex flex-col items-center">
        <div className="mx-auto font-thin">Remaining</div>
        <h1 className=" scroll-m-20 text-white text-7xl font-bold z-10 tracking-tight lg:text-5xl border-white">
          {remainingTime}
        </h1>
        <div className="mx-auto font-thin">seconds</div>
      </div>
    );
  };

  return (
    <>
      <CountdownCircleTimer
        isPlaying
        duration={time / 1000}
        colors={["#4ade80", "#4ade80", "#4ade80", "#4ade80"]}
        colorsTime={[7, 5, 2, 0]}
        size={225}
      >
        {renderTime}
      </CountdownCircleTimer>
    </>
  );
}

export default Countdown;
