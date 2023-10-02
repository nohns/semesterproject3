/** @format */

import httpMock from "@/api/axios.mock";
import {
  Beverage,
  BeverageType,
  GetBeveragesResponse,
  Status,
} from "@/api/protos/beverage/v1/beverage_pb.ts";

//sconst url = new RegExp(/v1\/event\/\d+$/);
const url = new RegExp(/v1\/beverages/); //I hate fucking regexes
httpMock.onGet(url).reply(() => {
  //Date time as string in rfc3339 format 30min from now

  const res = new GetBeveragesResponse({
    beverages: [
      //BEERS
      new Beverage({
        id: "1",
        price: "20",
        name: "IPA Beer",
        percentageChange: BigInt(5),
        type: BeverageType.BEER,
        status: Status.INCREASING,
      }),
      new Beverage({
        id: "2",
        price: "12",
        name: "Ceres Top",
        percentageChange: BigInt(-10),
        type: BeverageType.BEER,
        status: Status.DECREASING,
      }),
      new Beverage({
        id: "3",
        price: "8",
        name: "Jule Bajer",
        percentageChange: BigInt(-5),
        type: BeverageType.BEER,
        status: Status.DECREASING,
      }),
      new Beverage({
        id: "4",
        price: "12",
        name: "Guiness",
        percentageChange: BigInt(-15),
        type: BeverageType.BEER,
        status: Status.DECREASING,
      }),
      new Beverage({
        id: "5",
        price: "8",
        name: "Tuborg Classic",
        percentageChange: BigInt(20),
        type: BeverageType.BEER,
        status: Status.INCREASING,
      }),
      //COCKTAILS

      new Beverage({
        id: "6",
        price: "25",
        name: "Blå vand",
        percentageChange: BigInt(20),
        type: BeverageType.COCKTAIL,
        status: Status.INCREASING,
      }),

      new Beverage({
        id: "7",
        price: "25",
        name: "Nguac",
        percentageChange: BigInt(5),
        type: BeverageType.COCKTAIL,
        status: Status.INCREASING,
      }),

      new Beverage({
        id: "8",
        price: "80",
        name: "Spejlæg",
        percentageChange: BigInt(0),
        type: BeverageType.COCKTAIL,
        status: Status.NO_CHANGE,
      }),

      new Beverage({
        id: "9",
        price: "25",
        name: "Snapse Kondi",
        percentageChange: BigInt(5),
        type: BeverageType.COCKTAIL,
        status: Status.INCREASING,
      }),

      new Beverage({
        id: "10",
        price: "20",
        name: "Kongen af Danmark",
        percentageChange: BigInt(-5),
        type: BeverageType.COCKTAIL,
        status: Status.DECREASING,
      }),

      new Beverage({
        id: "11",
        price: "10",
        name: "Tequila",
        percentageChange: BigInt(15),
        type: BeverageType.SHOTS,
        status: Status.INCREASING,
      }),

      new Beverage({
        id: "12",
        price: "15",
        name: "Snaps",
        percentageChange: BigInt(0),
        type: BeverageType.SHOTS,
        status: Status.NO_CHANGE,
      }),

      new Beverage({
        id: "13",
        price: "12",
        name: "Små fugle",
        percentageChange: BigInt(-10),
        type: BeverageType.SHOTS,
        status: Status.DECREASING,
      }),

      new Beverage({
        id: "14",
        price: "10",
        name: "Sambuca",
        percentageChange: BigInt(15),
        type: BeverageType.SHOTS,
        status: Status.INCREASING,
      }),

      new Beverage({
        id: "15",
        price: "15",
        name: "Gammel Dansk",
        percentageChange: BigInt(-5),
        type: BeverageType.SHOTS,
        status: Status.DECREASING,
      }),
    ],
  });

  return [200, res];
});
