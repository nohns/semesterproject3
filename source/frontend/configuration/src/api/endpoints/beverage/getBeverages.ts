/** @format */
import ENV from "@/constants/env";
import { GetBeveragesResponse } from "@/api/protos/beverage/v1/beverage_pb.ts";

import { useQuery } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./getBeverages.mock.ts");
}

//This function I might actually be able to
const getBeverages = async () => {
  const { data } = await http.get(`v1/beverages`);

  return data as GetBeveragesResponse;
};

const useGetBeverages = () => {
  const { data, isLoading, error } = useQuery({
    queryKey: ["useGetBeverages"],
    queryFn: () => getBeverages(),
  });

  if (error) {
    console.error(error);
  }

  return { data, isLoading, error };
};

export default useGetBeverages;
