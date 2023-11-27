function RefillGuide(): JSX.Element {
  return (
    <div className="bg-sky-700 rounded-2xl w-96 flex flex-col items-center gap-5 p-2 text-white font-mono text-center">
      <h1>HOW TO REFILL DRINKSMACHINE</h1>
      <p>1. Open the lid</p>
      <p>2. empty the container</p>
      <p>3. put cup on the base </p>
      <p>4. tap the "clean container button" on the touchscreen </p>
      <p>5. wait until the container is clean</p>
      <p>6. refill the container with the chosen liquid</p>
      <p>7. close the lid</p>
      <div className="bg-cyan-400 rounded-xl mt-3 py-4 px-8 transition duration-300 hover:bg-emerald-500">
        Done
      </div>
    </div>
  );
}

export default RefillGuide;
