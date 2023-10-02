/** @format */

import httpMock from "@/api/axios.mock";
import { GetEventResponse } from "@/api/protos/event/v1/event_pb";

//sconst url = new RegExp(/v1\/event\/\d+$/);
const url = new RegExp(/v1\/event/); //I hate fucking regexes
httpMock.onGet(url).reply(() => {
  //Date time as string in rfc3339 format 30min from now
  const now = new Date();
  now.setMinutes(now.getMinutes() + 30);
  const nowString = now.toISOString();

  const res = new GetEventResponse({
    id: "123",
    futureTimestamp: nowString,
  });

  return [200, res];
});
