open UserDataType;

let unsafeGetUserName = ({userName}) => userName |> OptionService.unsafeGet;

let setUserName = (userName, record) => {
  ...record,
  userName: Some(userName),
};

let unsafeGetProfilePath = ({profilePath}) =>
  profilePath |> OptionService.unsafeGet;

let setProfilePath = (profilePath, record) => {
  ...record,
  profilePath: Some(profilePath),
};

let unsafeGetEmail = ({email}) => email |> OptionService.unsafeGet;

let setEmail = (email, record) => {...record, email: Some(email)};

let unsafeGetCurrentRepo = ({currentRepo}) =>
  currentRepo |> OptionService.unsafeGet;

let setCurrentRepo = (currentRepo, record) => {
  ...record,
  currentRepo: Some(currentRepo),
};

let unsafeGetUserRepos = ({userRepos}) =>
  userRepos |> OptionService.unsafeGet;

let setUserRepos = (userRepos, record) => {
  ...record,
  userRepos: Some(userRepos),
};