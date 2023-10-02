/** @format */
import ENV from "@/constants/env";
import { GetEventResponse } from "@/api/protos/event/v1/event_pb.ts";

import { useQuery } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./getEvent.mock.ts");
}

//This function I might actually be able to
const GetEvent = async () => {
  const { data } = await http.get(`v1/event`);

  return data as GetEventResponse;
};

const useGetEvent = () => {
  const { data, isLoading, error } = useQuery({
    queryKey: ["useGetEvent"],
    queryFn: () => GetEvent(),
  });

  if (error) {
    console.error(error);
  }

  return { data, isLoading, error };
};

export default useGetEvent;
